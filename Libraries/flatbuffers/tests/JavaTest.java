/*
 * Copyright 2014 Google Inc. All rights reserved.
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *     http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

import java.util.Arrays;
import java.math.BigInteger;
import java.io.*;
import java.nio.ByteBuffer;
import java.nio.ByteOrder;
import java.nio.channels.FileChannel;
import MyGame.Example.*;
import NamespaceA.*;
import NamespaceA.NamespaceB.*;
import com.google.flatbuffers.ByteBufferUtil;
import static com.google.flatbuffers.Constants.*;
import com.google.flatbuffers.FlatBufferBuilder;
import com.google.flatbuffers.FlexBuffersBuilder;
import com.google.flatbuffers.FlexBuffers;
import MyGame.MonsterExtra;

class JavaTest {
    public static void main(String[] args) {

        // First, let's test reading a FlatBuffer generated by C++ code:
        // This file was generated from monsterdata_test.json

        byte[] data = null;
        File file = new File("monsterdata_test.mon");
        RandomAccessFile f = null;
        try {
            f = new RandomAccessFile(file, "r");
            data = new byte[(int)f.length()];
            f.readFully(data);
            f.close();
        } catch(java.io.IOException e) {
            System.out.println("FlatBuffers test: couldn't read file");
            return;
        }

        // Now test it:

        ByteBuffer bb = ByteBuffer.wrap(data);
        TestBuffer(bb);

        // Second, let's create a FlatBuffer from scratch in Java, and test it also.
        // We use an initial size of 1 to exercise the reallocation algorithm,
        // normally a size larger than the typical FlatBuffer you generate would be
        // better for performance.
        FlatBufferBuilder fbb = new FlatBufferBuilder(1);

        TestBuilderBasics(fbb, true);
        TestBuilderBasics(fbb, false);

        TestExtendedBuffer(fbb.dataBuffer().asReadOnlyBuffer());

        TestNamespaceNesting();

        TestNestedFlatBuffer();

        TestCreateByteVector();

        TestCreateUninitializedVector();

        TestByteBufferFactory();

        TestSizedInputStream();

        TestVectorOfUnions();

        TestFixedLengthArrays();

        TestFlexBuffers();

        System.out.println("FlatBuffers test: completed successfully");
    }

    static void TestEnums() {
      TestEq(Color.name(Color.Red), "Red");
      TestEq(Color.name(Color.Blue), "Blue");
      TestEq(Any.name(Any.NONE), "NONE");
      TestEq(Any.name(Any.Monster), "Monster");
    }

    static void TestBuffer(ByteBuffer bb) {
        TestEq(Monster.MonsterBufferHasIdentifier(bb), true);

        Monster monster = Monster.getRootAsMonster(bb);

        TestEq(monster.hp(), (short)80);
        TestEq(monster.mana(), (short)150);  // default

        TestEq(monster.name(), "MyMonster");
        // monster.friendly() // can't access, deprecated

        Vec3 pos = monster.pos();
        TestEq(pos.x(), 1.0f);
        TestEq(pos.y(), 2.0f);
        TestEq(pos.z(), 3.0f);
        TestEq(pos.test1(), 3.0);
        // issue: int != byte
        TestEq(pos.test2(), (int) Color.Green);
        Test t = pos.test3();
        TestEq(t.a(), (short)5);
        TestEq(t.b(), (byte)6);

        TestEq(monster.testType(), (byte)Any.Monster);
        Monster monster2 = new Monster();
        TestEq(monster.test(monster2) != null, true);
        TestEq(monster2.name(), "Fred");

        TestEq(monster.inventoryLength(), 5);
        int invsum = 0;
        for (int i = 0; i < monster.inventoryLength(); i++)
            invsum += monster.inventory(i);
        TestEq(invsum, 10);

        // Alternative way of accessing a vector:
        ByteBuffer ibb = monster.inventoryAsByteBuffer();
        invsum = 0;
        while (ibb.position() < ibb.limit())
            invsum += ibb.get();
        TestEq(invsum, 10);

        Test test_0 = monster.test4(0);
        Test test_1 = monster.test4(1);
        TestEq(monster.test4Length(), 2);
        TestEq(test_0.a() + test_0.b() + test_1.a() + test_1.b(), 100);

        TestEq(monster.testarrayofstringLength(), 2);
        TestEq(monster.testarrayofstring(0),"test1");
        TestEq(monster.testarrayofstring(1),"test2");

        TestEq(monster.testbool(), true);
    }

    // this method checks additional fields not present in the binary buffer read from file
    // these new tests are performed on top of the regular tests
    static void TestExtendedBuffer(ByteBuffer bb) {
        TestBuffer(bb);

        Monster monster = Monster.getRootAsMonster(bb);

        TestEq(monster.testhashu32Fnv1(), Integer.MAX_VALUE + 1L);
    }

    static void TestNamespaceNesting() {
        // reference / manipulate these to verify compilation
        FlatBufferBuilder fbb = new FlatBufferBuilder(1);

        TableInNestedNS.startTableInNestedNS(fbb);
        TableInNestedNS.addFoo(fbb, 1234);
        int nestedTableOff = TableInNestedNS.endTableInNestedNS(fbb);

        TableInFirstNS.startTableInFirstNS(fbb);
        TableInFirstNS.addFooTable(fbb, nestedTableOff);
        int off = TableInFirstNS.endTableInFirstNS(fbb);
    }

    static void TestNestedFlatBuffer() {
        final String nestedMonsterName = "NestedMonsterName";
        final short nestedMonsterHp = 600;
        final short nestedMonsterMana = 1024;

        FlatBufferBuilder fbb1 = new FlatBufferBuilder(16);
        int str1 = fbb1.createString(nestedMonsterName);
        Monster.startMonster(fbb1);
        Monster.addName(fbb1, str1);
        Monster.addHp(fbb1, nestedMonsterHp);
        Monster.addMana(fbb1, nestedMonsterMana);
        int monster1 = Monster.endMonster(fbb1);
        Monster.finishMonsterBuffer(fbb1, monster1);
        byte[] fbb1Bytes = fbb1.sizedByteArray();
        fbb1 = null;

        FlatBufferBuilder fbb2 = new FlatBufferBuilder(16);
        int str2 = fbb2.createString("My Monster");
        int nestedBuffer = Monster.createTestnestedflatbufferVector(fbb2, fbb1Bytes);
        Monster.startMonster(fbb2);
        Monster.addName(fbb2, str2);
        Monster.addHp(fbb2, (short)50);
        Monster.addMana(fbb2, (short)32);
        Monster.addTestnestedflatbuffer(fbb2, nestedBuffer);
        int monster = Monster.endMonster(fbb2);
        Monster.finishMonsterBuffer(fbb2, monster);

        // Now test the data extracted from the nested buffer
        Monster mons = Monster.getRootAsMonster(fbb2.dataBuffer());
        Monster nestedMonster = mons.testnestedflatbufferAsMonster();

        TestEq(nestedMonsterMana, nestedMonster.mana());
        TestEq(nestedMonsterHp, nestedMonster.hp());
        TestEq(nestedMonsterName, nestedMonster.name());
    }

    static void TestCreateByteVector() {
        FlatBufferBuilder fbb = new FlatBufferBuilder(16);
        int str = fbb.createString("MyMonster");
        byte[] inventory = new byte[] { 0, 1, 2, 3, 4 };
        int vec = fbb.createByteVector(inventory);
        Monster.startMonster(fbb);
        Monster.addInventory(fbb, vec);
        Monster.addName(fbb, str);
        int monster1 = Monster.endMonster(fbb);
        Monster.finishMonsterBuffer(fbb, monster1);
        Monster monsterObject = Monster.getRootAsMonster(fbb.dataBuffer());

        TestEq(monsterObject.inventory(1), (int)inventory[1]);
        TestEq(monsterObject.inventoryLength(), inventory.length);
        TestEq(ByteBuffer.wrap(inventory), monsterObject.inventoryAsByteBuffer());
    }

    static void TestCreateUninitializedVector() {
        FlatBufferBuilder fbb = new FlatBufferBuilder(16);
        int str = fbb.createString("MyMonster");
        byte[] inventory = new byte[] { 0, 1, 2, 3, 4 };
        ByteBuffer bb = fbb.createUnintializedVector(1, inventory.length, 1);
        for (byte i:inventory) {
            bb.put(i);
        }
        int vec = fbb.endVector();
        Monster.startMonster(fbb);
        Monster.addInventory(fbb, vec);
        Monster.addName(fbb, str);
        int monster1 = Monster.endMonster(fbb);
        Monster.finishMonsterBuffer(fbb, monster1);
        Monster monsterObject = Monster.getRootAsMonster(fbb.dataBuffer());

        TestEq(monsterObject.inventory(1), (int)inventory[1]);
        TestEq(monsterObject.inventoryLength(), inventory.length);
        TestEq(ByteBuffer.wrap(inventory), monsterObject.inventoryAsByteBuffer());
    }

    static void TestByteBufferFactory() {
        final class MappedByteBufferFactory extends FlatBufferBuilder.ByteBufferFactory {
            @Override
            public ByteBuffer newByteBuffer(int capacity) {
                ByteBuffer bb;
                try {
                    RandomAccessFile f = new RandomAccessFile("javatest.bin", "rw");
                    bb =  f.getChannel().map(FileChannel.MapMode.READ_WRITE, 0, capacity).order(ByteOrder.LITTLE_ENDIAN);
                    f.close();
                } catch(Throwable e) {
                    System.out.println("FlatBuffers test: couldn't map ByteBuffer to a file");
                    bb = null;
                }
                return bb;
            }
        }

        FlatBufferBuilder fbb = new FlatBufferBuilder(1, new MappedByteBufferFactory());

        TestBuilderBasics(fbb, false);
    }

    static void TestSizedInputStream() {
        // Test on default FlatBufferBuilder that uses HeapByteBuffer
        FlatBufferBuilder fbb = new FlatBufferBuilder(1);

        TestBuilderBasics(fbb, false);

        InputStream in = fbb.sizedInputStream();
        byte[] array = fbb.sizedByteArray();
        int count = 0;
        int currentVal = 0;

        while (currentVal != -1 && count < array.length) {
            try {
                currentVal = in.read();
            } catch(java.io.IOException e) {
                System.out.println("FlatBuffers test: couldn't read from InputStream");
                return;
            }
            TestEq((byte)currentVal, array[count]);
            count++;
        }
        TestEq(count, array.length);
    }

    static void TestBuilderBasics(FlatBufferBuilder fbb, boolean sizePrefix) {
        int[] names = {fbb.createString("Frodo"), fbb.createString("Barney"), fbb.createString("Wilma")};
        int[] off = new int[3];
        Monster.startMonster(fbb);
        Monster.addName(fbb, names[0]);
        off[0] = Monster.endMonster(fbb);
        Monster.startMonster(fbb);
        Monster.addName(fbb, names[1]);
        off[1] = Monster.endMonster(fbb);
        Monster.startMonster(fbb);
        Monster.addName(fbb, names[2]);
        off[2] = Monster.endMonster(fbb);
        int sortMons = fbb.createSortedVectorOfTables(new Monster(), off);

        // We set up the same values as monsterdata.json:

        int str = fbb.createString("MyMonster");

        int inv = Monster.createInventoryVector(fbb, new byte[] { 0, 1, 2, 3, 4 });

        int fred = fbb.createString("Fred");
        Monster.startMonster(fbb);
        Monster.addName(fbb, fred);
        int mon2 = Monster.endMonster(fbb);

        Monster.startTest4Vector(fbb, 2);
        Test.createTest(fbb, (short)10, (byte)20);
        Test.createTest(fbb, (short)30, (byte)40);
        int test4 = fbb.endVector();

        int testArrayOfString = Monster.createTestarrayofstringVector(fbb, new int[] {
                fbb.createString("test1"),
                fbb.createString("test2")
        });

        Monster.startMonster(fbb);
        Monster.addPos(fbb, Vec3.createVec3(fbb, 1.0f, 2.0f, 3.0f, 3.0,
                Color.Green, (short)5, (byte)6));
        Monster.addHp(fbb, (short)80);
        Monster.addName(fbb, str);
        Monster.addInventory(fbb, inv);
        Monster.addTestType(fbb, (byte)Any.Monster);
        Monster.addTest(fbb, mon2);
        Monster.addTest4(fbb, test4);
        Monster.addTestarrayofstring(fbb, testArrayOfString);
        Monster.addTestbool(fbb, true);
        Monster.addTesthashu32Fnv1(fbb, Integer.MAX_VALUE + 1L);
        Monster.addTestarrayoftables(fbb, sortMons);
        int mon = Monster.endMonster(fbb);

        if (sizePrefix) {
            Monster.finishSizePrefixedMonsterBuffer(fbb, mon);
        } else {
            Monster.finishMonsterBuffer(fbb, mon);
        }

        // Write the result to a file for debugging purposes:
        // Note that the binaries are not necessarily identical, since the JSON
        // parser may serialize in a slightly different order than the above
        // Java code. They are functionally equivalent though.

        try {
            String filename = "monsterdata_java_wire" + (sizePrefix ? "_sp" : "") + ".mon";
            FileChannel fc = new FileOutputStream(filename).getChannel();
            fc.write(fbb.dataBuffer().duplicate());
            fc.close();
        } catch(java.io.IOException e) {
            System.out.println("FlatBuffers test: couldn't write file");
            return;
        }

        // Test it:
        ByteBuffer dataBuffer = fbb.dataBuffer();
        if (sizePrefix) {
            TestEq(ByteBufferUtil.getSizePrefix(dataBuffer) + SIZE_PREFIX_LENGTH,
                   dataBuffer.remaining());
            dataBuffer = ByteBufferUtil.removeSizePrefix(dataBuffer);
        }
        TestExtendedBuffer(dataBuffer);

        // Make sure it also works with read only ByteBuffers. This is slower,
        // since creating strings incurs an additional copy
        // (see Table.__string).
        TestExtendedBuffer(dataBuffer.asReadOnlyBuffer());

        TestEnums();

        //Attempt to mutate Monster fields and check whether the buffer has been mutated properly
        // revert to original values after testing
        Monster monster = Monster.getRootAsMonster(dataBuffer);

        // mana is optional and does not exist in the buffer so the mutation should fail
        // the mana field should retain its default value
        TestEq(monster.mutateMana((short)10), false);
        TestEq(monster.mana(), (short)150);

        // Accessing a vector of sorted by the key tables
        TestEq(monster.testarrayoftables(0).name(), "Barney");
        TestEq(monster.testarrayoftables(1).name(), "Frodo");
        TestEq(monster.testarrayoftables(2).name(), "Wilma");

        // Example of searching for a table by the key
        TestEq(monster.testarrayoftablesByKey("Frodo").name(), "Frodo");
        TestEq(monster.testarrayoftablesByKey("Barney").name(), "Barney");
        TestEq(monster.testarrayoftablesByKey("Wilma").name(), "Wilma");

        // testType is an existing field and mutating it should succeed
        TestEq(monster.testType(), (byte)Any.Monster);
        TestEq(monster.mutateTestType(Any.NONE), true);
        TestEq(monster.testType(), (byte)Any.NONE);
        TestEq(monster.mutateTestType(Any.Monster), true);
        TestEq(monster.testType(), (byte)Any.Monster);

        //mutate the inventory vector
        TestEq(monster.mutateInventory(0, 1), true);
        TestEq(monster.mutateInventory(1, 2), true);
        TestEq(monster.mutateInventory(2, 3), true);
        TestEq(monster.mutateInventory(3, 4), true);
        TestEq(monster.mutateInventory(4, 5), true);

        for (int i = 0; i < monster.inventoryLength(); i++) {
            TestEq(monster.inventory(i), i + 1);
        }

        //reverse mutation
        TestEq(monster.mutateInventory(0, 0), true);
        TestEq(monster.mutateInventory(1, 1), true);
        TestEq(monster.mutateInventory(2, 2), true);
        TestEq(monster.mutateInventory(3, 3), true);
        TestEq(monster.mutateInventory(4, 4), true);

        // get a struct field and edit one of its fields
        Vec3 pos = monster.pos();
        TestEq(pos.x(), 1.0f);
        pos.mutateX(55.0f);
        TestEq(pos.x(), 55.0f);
        pos.mutateX(1.0f);
        TestEq(pos.x(), 1.0f);
    }

    static void TestVectorOfUnions() {
        final FlatBufferBuilder fbb = new FlatBufferBuilder();

        final int swordAttackDamage = 1;

        final int[] characterVector = new int[] {
            Attacker.createAttacker(fbb, swordAttackDamage),
        };

        final byte[] characterTypeVector = new byte[]{
            Character.MuLan,
        };

        Movie.finishMovieBuffer(
            fbb,
            Movie.createMovie(
                fbb,
                (byte)0,
                (byte)0,
                Movie.createCharactersTypeVector(fbb, characterTypeVector),
                Movie.createCharactersVector(fbb, characterVector)
            )
        );

        final Movie movie = Movie.getRootAsMovie(fbb.dataBuffer());

        TestEq(movie.charactersTypeLength(), characterTypeVector.length);
        TestEq(movie.charactersLength(), characterVector.length);

        TestEq(movie.charactersType(0), characterTypeVector[0]);

        TestEq(((Attacker)movie.characters(new Attacker(), 0)).swordAttackDamage(), swordAttackDamage);
    }

    static void TestFixedLengthArrays() {
        FlatBufferBuilder builder = new FlatBufferBuilder(0);

        float       a;
        int[]       b = new int[15];
        byte        c;
        int[][]     d_a = new int[2][2];
        byte[]      d_b = new byte[2];
        byte[][]    d_c = new byte[2][2];
        long[][]    d_d = new long[2][2];
        int         e;
        long[]      f = new long[2];

        a = 0.5f;
        for (int i = 0; i < 15; i++) b[i] = i;
        c = 1;
        d_a[0][0] = 1;
        d_a[0][1] = 2;
        d_a[1][0] = 3;
        d_a[1][1] = 4;
        d_b[0] = TestEnum.B;
        d_b[1] = TestEnum.C;
        d_c[0][0] = TestEnum.A;
        d_c[0][1] = TestEnum.B;
        d_c[1][0] = TestEnum.C;
        d_c[1][1] = TestEnum.B;
        d_d[0][0] = -1;
        d_d[0][1] = 1;
        d_d[1][0] = -2;
        d_d[1][1] = 2;
        e = 2;
        f[0] = -1;
        f[1] = 1;

        int arrayOffset = ArrayStruct.createArrayStruct(builder,
            a, b, c, d_a, d_b, d_c, d_d, e, f);

        // Create a table with the ArrayStruct.
        ArrayTable.startArrayTable(builder);
        ArrayTable.addA(builder, arrayOffset);
        int tableOffset = ArrayTable.endArrayTable(builder);

        ArrayTable.finishArrayTableBuffer(builder, tableOffset);

        ArrayTable table = ArrayTable.getRootAsArrayTable(builder.dataBuffer());
        NestedStruct nested = new NestedStruct();

        TestEq(table.a().a(), 0.5f);
        for (int i = 0; i < 15; i++) TestEq(table.a().b(i), i);
        TestEq(table.a().c(), (byte)1);
        TestEq(table.a().d(nested, 0).a(0), 1);
        TestEq(table.a().d(nested, 0).a(1), 2);
        TestEq(table.a().d(nested, 1).a(0), 3);
        TestEq(table.a().d(nested, 1).a(1), 4);
        TestEq(table.a().d(nested, 0).b(), TestEnum.B);
        TestEq(table.a().d(nested, 1).b(), TestEnum.C);
        TestEq(table.a().d(nested, 0).c(0), TestEnum.A);
        TestEq(table.a().d(nested, 0).c(1), TestEnum.B);
        TestEq(table.a().d(nested, 1).c(0), TestEnum.C);
        TestEq(table.a().d(nested, 1).c(1), TestEnum.B);
        TestEq(table.a().d(nested, 0).d(0), (long)-1);
        TestEq(table.a().d(nested, 0).d(1), (long)1);
        TestEq(table.a().d(nested, 1).d(0), (long)-2);
        TestEq(table.a().d(nested, 1).d(1), (long)2);
        TestEq(table.a().e(), 2);
        TestEq(table.a().f(0), (long)-1);
        TestEq(table.a().f(1), (long)1);
    }

    public static void testFlexBuffersTest() {
        FlexBuffersBuilder builder = new FlexBuffersBuilder(ByteBuffer.allocate(512),
                FlexBuffersBuilder.BUILDER_FLAG_SHARE_KEYS_AND_STRINGS);

        // Write the equivalent of:
        // { vec: [ -100, "Fred", 4.0, false ], bar: [ 1, 2, 3 ], bar3: [ 1, 2, 3 ],
        // foo: 100, bool: true, mymap: { foo: "Fred" } }
        // It's possible to do this without std::function support as well.
        int map1 = builder.startMap();

        int vec1 = builder.startVector();
        builder.putInt(-100);
        builder.putString("Fred");
        builder.putBlob(new byte[]{(byte) 77});
        builder.putBoolean(false);
        builder.putInt(Long.MAX_VALUE);

        int map2 = builder.startMap();
        builder.putInt("test", 200);
        builder.endMap(null, map2);

        builder.putFloat(150.9);
        builder.putFloat(150.9999998);
        builder.endVector("vec", vec1, false, false);

        vec1 = builder.startVector();
        builder.putInt(1);
        builder.putInt(2);
        builder.putInt(3);
        builder.endVector("bar", vec1, true, false);

        vec1 = builder.startVector();
        builder.putBoolean(true);
        builder.putBoolean(false);
        builder.putBoolean(true);
        builder.putBoolean(false);
        builder.endVector("bools", vec1, true, false);

        builder.putBoolean("bool", true);
        builder.putFloat("foo", 100);

        map2 = builder.startMap();
        builder.putString("bar", "Fred");  // Testing key and string reuse.
        builder.putInt("int", -120);
        builder.putFloat("float", -123.0f);
        builder.putBlob("blob", new byte[]{ 65, 67 });
        builder.endMap("mymap", map2);

        builder.endMap(null, map1);
        builder.finish();

        FlexBuffers.Map m = FlexBuffers.getRoot(builder.getBuffer()).asMap();

        TestEq(m.size(), 6);

        // test empty (an null)
        TestEq(m.get("no_key").asString(), ""); // empty if fail
        TestEq(m.get("no_key").asMap(), FlexBuffers.Map.empty()); // empty if fail
        TestEq(m.get("no_key").asKey(), FlexBuffers.Key.empty()); // empty if fail
        TestEq(m.get("no_key").asVector(), FlexBuffers.Vector.empty()); // empty if fail
        TestEq(m.get("no_key").asBlob(), FlexBuffers.Blob.empty()); // empty if fail
        assert(m.get("no_key").asVector().isEmpty()); // empty if fail

        // testing "vec" field
        FlexBuffers.Vector vec = m.get("vec").asVector();
        TestEq(vec.size(), 8);
        TestEq(vec.get(0).asLong(), (long) -100);
        TestEq(vec.get(1).asString(), "Fred");
        TestEq(vec.get(2).isBlob(), true);
        TestEq(vec.get(2).asBlob().size(), 1);
        TestEq(vec.get(2).asBlob().data().get(0), (byte) 77);
        TestEq(vec.get(3).isBoolean(), true);   // Check if type is a bool
        TestEq(vec.get(3).asBoolean(), false);  // Check if value is false
        TestEq(vec.get(4).asLong(), Long.MAX_VALUE);
        TestEq(vec.get(5).isMap(), true);
        TestEq(vec.get(5).asMap().get("test").asInt(), 200);
        TestEq(Float.compare((float)vec.get(6).asFloat(), 150.9f), 0);
        TestEq(Double.compare(vec.get(7).asFloat(), 150.9999998), 0);
        TestEq((long)0, (long)vec.get(1).asLong()); //conversion fail returns 0 as C++

        // bar vector
        FlexBuffers.Vector tvec = m.get("bar").asVector();
        TestEq(tvec.size(), 3);
        TestEq(tvec.get(0).asInt(), 1);
        TestEq(tvec.get(1).asInt(), 2);
        TestEq(tvec.get(2).asInt(), 3);
        TestEq(((FlexBuffers.TypedVector) tvec).getElemType(), FlexBuffers.FBT_INT);

        // bools vector
        FlexBuffers.Vector bvec = m.get("bools").asVector();
        TestEq(bvec.size(), 4);
        TestEq(bvec.get(0).asBoolean(), true);
        TestEq(bvec.get(1).asBoolean(), false);
        TestEq(bvec.get(2).asBoolean(), true);
        TestEq(bvec.get(3).asBoolean(), false);
        TestEq(((FlexBuffers.TypedVector) bvec).getElemType(), FlexBuffers.FBT_BOOL);


        TestEq((float)m.get("foo").asFloat(), (float) 100);
        TestEq(m.get("unknown").isNull(), true);

        // mymap vector
        FlexBuffers.Map mymap = m.get("mymap").asMap();
        TestEq(mymap.keys().get(0), m.keys().get(0)); // These should be equal by pointer equality, since key and value are shared.
        TestEq(mymap.values().get(0).asString(), vec.get(1).asString());
        TestEq(mymap.get("int").asInt(), -120);
        TestEq((float)mymap.get("float").asFloat(), -123.0f);
        TestEq(Arrays.equals(mymap.get("blob").asBlob().getBytes(), new byte[]{ 65, 67 }), true);
        TestEq(mymap.get("blob").asBlob().toString(), "AC");
        TestEq(mymap.get("blob").toString(), "\"AC\"");
    }

    public static void testSingleElementBoolean() {
        FlexBuffersBuilder builder = new FlexBuffersBuilder(ByteBuffer.allocate(100));
        builder.putBoolean(true);
        ByteBuffer b = builder.finish();
        assert(FlexBuffers.getRoot(b).asBoolean());
    }

    public static void testSingleElementByte() {
        FlexBuffersBuilder builder = new FlexBuffersBuilder();
        builder.putInt(10);
        ByteBuffer b = builder.finish();
        TestEq(10, FlexBuffers.getRoot(b).asInt());
    }

    public static void testSingleElementShort() {
        FlexBuffersBuilder builder = new FlexBuffersBuilder();
        builder.putInt(Short.MAX_VALUE);
        ByteBuffer b = builder.finish();
        TestEq(Short.MAX_VALUE, (short)FlexBuffers.getRoot(b).asInt());
    }

    public static void testSingleElementInt() {
        FlexBuffersBuilder builder = new FlexBuffersBuilder();
        builder.putInt(Integer.MIN_VALUE);
        ByteBuffer b = builder.finish();
        TestEq(Integer.MIN_VALUE, FlexBuffers.getRoot(b).asInt());
    }

    public static void testSingleElementLong() {
        FlexBuffersBuilder builder = new FlexBuffersBuilder();
        builder.putInt(Long.MAX_VALUE);
        ByteBuffer b = builder.finish();
        TestEq(Long.MAX_VALUE, FlexBuffers.getRoot(b).asLong());
    }

    public static void testSingleElementFloat() {
        FlexBuffersBuilder builder = new FlexBuffersBuilder();
        builder.putFloat(Float.MAX_VALUE);
        ByteBuffer b = builder.finish();
        TestEq(Float.compare(Float.MAX_VALUE, (float) FlexBuffers.getRoot(b).asFloat()), 0);
    }

    public static void testSingleElementDouble() {
        FlexBuffersBuilder builder = new FlexBuffersBuilder();
        builder.putFloat(Double.MAX_VALUE);
        ByteBuffer b = builder.finish();
        TestEq(Double.compare(Double.MAX_VALUE, FlexBuffers.getRoot(b).asFloat()), 0);
    }

    public static void testSingleElementString() {
        FlexBuffersBuilder builder = new FlexBuffersBuilder();
        builder.putString("wow");
        ByteBuffer b = builder.finish();
        FlexBuffers.Reference r = FlexBuffers.getRoot(b);
        TestEq(FlexBuffers.FBT_STRING, r.getType());
        TestEq("wow", r.asString());
    }

    public static void testSingleElementBlob() {
        FlexBuffersBuilder builder = new FlexBuffersBuilder();
        builder.putBlob(new byte[]{5, 124, 118, -1});
        ByteBuffer b = builder.finish();
        FlexBuffers.Reference r = FlexBuffers.getRoot(b);
        byte[] result = r.asBlob().getBytes();
        TestEq((byte)5, result[0]);
        TestEq((byte)124, result[1]);
        TestEq((byte)118, result[2]);
        TestEq((byte)-1, result[3]);
    }

    public static void testSingleElementUByte() {
        FlexBuffersBuilder builder = new FlexBuffersBuilder();
        builder.putUInt(0xFF);
        ByteBuffer b = builder.finish();
        FlexBuffers.Reference r = FlexBuffers.getRoot(b);
        TestEq(255, (int)r.asUInt());
    }

    public static void testSingleElementUShort() {
        FlexBuffersBuilder builder = new FlexBuffersBuilder();
        builder.putUInt(0xFFFF);
        ByteBuffer b = builder.finish();
        FlexBuffers.Reference r = FlexBuffers.getRoot(b);
        TestEq(65535, (int)r.asUInt());
    }

    public static void testSingleElementUInt() {
        FlexBuffersBuilder builder = new FlexBuffersBuilder();
        builder.putUInt(0xFFFF_FFFFL);
        ByteBuffer b = builder.finish();
        FlexBuffers.Reference r = FlexBuffers.getRoot(b);
        TestEq(4294967295L, r.asUInt());
    }

    public static void testSingleFixedTypeVector() {

        int[] ints = new int[]{5, 124, 118, -1};
        float[] floats = new float[]{5.5f, 124.124f, 118.118f, -1.1f};
        String[] strings = new String[]{"This", "is", "a", "typed", "array"};
        boolean[] booleans = new boolean[]{false, true, true, false};


        FlexBuffersBuilder builder = new FlexBuffersBuilder(ByteBuffer.allocate(512),
                FlexBuffersBuilder.BUILDER_FLAG_NONE);

        int mapPos = builder.startMap();

        int vecPos = builder.startVector();
        for (final int i : ints) {
            builder.putInt(i);
        }
        builder.endVector("ints", vecPos, true, false);

        vecPos = builder.startVector();
        for (final float i : floats) {
            builder.putFloat(i);
        }
        builder.endVector("floats", vecPos, true, false);

        vecPos = builder.startVector();
        for (final String i : strings) {
            builder.putString(i);
        }
        builder.endVector("strings", vecPos, true, false);

        vecPos = builder.startVector();
        for (final boolean i : booleans) {
            builder.putBoolean(i);
        }
        builder.endVector("booleans", vecPos, true, false);

        builder.endMap(null, mapPos);


        ByteBuffer b = builder.finish();
        FlexBuffers.Reference r = FlexBuffers.getRoot(b);
        assert(r.asMap().get("ints").isTypedVector());
        assert(r.asMap().get("floats").isTypedVector());
        assert(r.asMap().get("strings").isTypedVector());
        assert(r.asMap().get("booleans").isTypedVector());
    }

    public static void testSingleElementVector() {
        FlexBuffersBuilder b = new FlexBuffersBuilder();

        int vecPos = b.startVector();
        b.putInt(99);
        b.putString("wow");
        int vecpos2 = b.startVector();
        b.putInt(99);
        b.putString("wow");
        b.endVector(null, vecpos2, false, false);
        b.endVector(null, vecPos, false, false);
        b.finish();

        FlexBuffers.Reference r = FlexBuffers.getRoot(b.getBuffer());
        TestEq(FlexBuffers.FBT_VECTOR, r.getType());
        FlexBuffers.Vector vec = FlexBuffers.getRoot(b.getBuffer()).asVector();
        TestEq(3, vec.size());
        TestEq(99, vec.get(0).asInt());
        TestEq("wow", vec.get(1).asString());
        TestEq("[ 99, \"wow\" ]", vec.get(2).toString());
        TestEq("[ 99, \"wow\", [ 99, \"wow\" ] ]", FlexBuffers.getRoot(b.getBuffer()).toString());
    }

    public static void testSingleElementMap() {
        FlexBuffersBuilder b = new FlexBuffersBuilder();

        int mapPost = b.startMap();
        b.putInt("myInt", 0x7fffffbbbfffffffL);
        b.putString("myString", "wow");
        b.putString("myString2", "incredible");
        int start = b.startVector();
        b.putInt(99);
        b.putString("wow");
        b.endVector("myVec", start, false, false);

        b.putFloat("double", 0x1.ffffbbbffffffP+1023);
        b.endMap(null, mapPost);
        b.finish();

        FlexBuffers.Reference r = FlexBuffers.getRoot(b.getBuffer());
        TestEq(FlexBuffers.FBT_MAP, r.getType());
        FlexBuffers.Map map = FlexBuffers.getRoot(b.getBuffer()).asMap();
        TestEq(5, map.size());
        TestEq(0x7fffffbbbfffffffL, map.get("myInt").asLong());
        TestEq("wow", map.get("myString").asString());
        TestEq("incredible", map.get("myString2").asString());
        TestEq(99, map.get("myVec").asVector().get(0).asInt());
        TestEq("wow", map.get("myVec").asVector().get(1).asString());
        TestEq(Double.compare(0x1.ffffbbbffffffP+1023, map.get("double").asFloat()), 0);
        TestEq("{ \"double\" : 1.7976894783391937E308, \"myInt\" : 9223371743723257855, \"myString\" : \"wow\", \"myString2\" : \"incredible\", \"myVec\" : [ 99, \"wow\" ] }",
                FlexBuffers.getRoot(b.getBuffer()).toString());
    }

    public static void TestFlexBuffers() {
        testSingleElementByte();
        testSingleElementShort();
        testSingleElementInt();
        testSingleElementLong();
        testSingleElementFloat();
        testSingleElementDouble();
        testSingleElementString();
        testSingleElementBlob();
        testSingleElementVector();
        testSingleFixedTypeVector();
        testSingleElementUShort();
        testSingleElementUInt();
        testSingleElementUByte();
        testSingleElementMap();
	testFlexBuffersTest();
    }

    static <T> void TestEq(T a, T b) {
        if (!a.equals(b)) {
            System.out.println("" + a.getClass().getName() + " " + b.getClass().getName());
            System.out.println("FlatBuffers test FAILED: \'" + a + "\' != \'" + b + "\'");
            new Throwable().printStackTrace();
            assert false;
            System.exit(1);
        }
    }
}
