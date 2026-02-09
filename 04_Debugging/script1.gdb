set pagination off

b 13 if x == 5
command 1
    echo @@@
    printf "%d %d %d", M, N, x
    echo @@@
    c
end

run 1 12 > /dev/null

quit
