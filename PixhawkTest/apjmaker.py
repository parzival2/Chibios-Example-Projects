class generate_apj(object):
    '''generate an apj firmware file'''
    color='CYAN'
    always_run = True
    def keyword(self):
        return "apj_gen"
    def run(self, binFile):
        import json, time, base64, zlib
        img = open(binFile,'rb').read()
        d = {
            "board_id": int(9),
            "magic": "APJFWv1",
            "description": "Firmware for a STM32F427xx board",
            "image": base64.b64encode(zlib.compress(img,9)).decode('utf-8'),
            "build_time": int(time.time()),
            "summary": "Pixhawk1",
            "version": "0.1",
            "image_size": len(img),
            "git_identity": "",
            "board_revision": 0
        }
        apj_file = "pixhawk_test.apj"
        f = open(apj_file, "w")
        f.write(json.dumps(d, indent=4))
        f.close()

if __name__ == '__main__':
    gen = generate_apj()
    gen.run(r"/home/kalyansreenivas/Projects/chibios_practice_programs/PixhawkTest/build/PixhawkTest.bin")

