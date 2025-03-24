comment(` Dylan Mumm')
comment(` CPSC 2310-002')
comment(` Assignment 1')
comment(` 9.28.2018')
comment(` Given an integer containing only 0s and 1s, program is to print its decimal equivalent.')
comment(` ')




word(N, 1101)
word(base, 1)
word(rem, 0)
word(ten, 10)
word(dec, 0)
word(temp, 0)
word(two, 2)






label(start)

    load(N)

label(loop)

    div(ten)
    mul(ten)
    store(temp)
    load(N)
    sub(temp)
    mul(base)
    store(rem)

    load(dec)
    add(rem)
    store(dec)

    load(N)
    div(ten)
    store(N)

    load(base)
    mul(two)
    store(base)

    load(N)
    bgt0(loop)

label(done)

    print(dec)
    halt

end(start)
