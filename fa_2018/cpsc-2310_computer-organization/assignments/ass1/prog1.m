comment(` Dylan Mumm                                                                             ')
comment(` CPSC 2310-002                                                                          ')
comment(` Assignment 1                                                                           ')
comment(` 9.28.2018                                                                              ')
comment(` Given an integer containing only 0s and 1s, program is to print its decimal equivalent.')


word(N, 1101)
word(base, 1)
word(rem, 0)
word(ten, 10)
word(dec, 0)
word(temp, 0)
word(two, 2)

label(start)

    load(N)        comment(`  loads binary number      ')

label(loop)

    div(ten)      comment(`  divides remaining binary number by 10                 ')
    mul(ten)      comment(`  then multiplies by ten to "shave off" remainder       ')
    store(temp)   comment(`  temporarily storing it                                ')
    load(N)       comment(`  and then subtracting original number by shaved        ')
    sub(temp)     comment(`  to find remainder                                     ')
    mul(base)     comment(`  and multiply it by current base                       ')
    store(rem)    comment(`  to store for later                                    ')

    load(dec)     comment(`  loads current decimal number, adds remainder, stores  ')
    add(rem)
    store(dec)

    load(N)       comment(`  remove already used place off binary number           ')
    div(ten)
    store(N)

    load(base)   comment(`  multiply base by two to prepare for next iteration     ')
    mul(two)
    store(base)

    load(N)      comment(`  branch if remaining binary is not yet 0                ')
    bgt0(loop)

label(done)

    print(dec)
    halt

end(start)
