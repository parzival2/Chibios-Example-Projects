printf "Debug Info\n"
printf "isr_cnt=%d\tlock_cnt=%d\ttm_cal=%d\tpanic=", ch.dbg.isr_cnt, ch.dbg.lock_cnt, ch.tm.offset
output ch.dbg.panic_msg
echo \n\n

printf "Thread stack used\n"
set $filler = 0x5555555555555555
set $max_stack_size = 0xFFFF
set $tp = ch.rlist.newer
set $ctr = 0
while $tp != &ch.rlist
    printf "%d, %s, ", $ctr, $tp->name
    output $tp->wabase
    if strcmp($tp->name, "main") != 0
        set $unused = 0
        set $stk_ptr = (uint64_t *)$tp->wabase
        while (*$stk_ptr == $filler) && ($unused < $max_stack_size)
            set $stk_ptr = $stk_ptr + 1
            set $unused = $unused + sizeof(uint64_t)
        end
        printf ", unused stack = %d", $unused
    end
    echo \n
    set $ctr = $ctr + 1
    set $tp = $tp->newer
end

