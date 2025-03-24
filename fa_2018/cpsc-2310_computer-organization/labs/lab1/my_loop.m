comment(` Dylan Mumm')
comment(` CPSC 2311 004')


comment(`  code that implements the loop                       ')
comment(`    sum = 0;                                          ')
comment(`    for( i = 1; i <= 10; i++) {                       ')
comment(`       sum = sum + i;                                 ')
comment(`    }                                                 ')

comment(`  set aside memory and initialize variables           ')


word(sum,0)
word(i,0)
word(zero,0)
word(one,1)
word(ten,10)

label(start)

comment(`  Note: in the rest of the program usually  ')
comment(`  more than one assembly code instruction   ')
comment(`  is needed for each C statement            ')
comment(`  sum = 0                                   ')

load(zero)  comment(`  ACC <- memory[zero]  load ACC with zero   ')
store(sum)  comment(`  memory[sum] <- ACC   store ACC to sum     ')

comment(`  i = 1                                    ')
load(one)   comment(`  ACC <- memory[ten]                        ')
store(i)    comment(`  memory[i] <- ACC                          ')


label(loop)

   load(i)     comment(`  branch to done if i > 10)             ')
   sub(ten)
   bgt0(done)

   load(sum)   comment(`  sum = sum + i                        ')
   add(i)
   store(sum)

   load(i)     comment(`  i = i + 1                            ')
   add(one)
   store(i)

   ba(loop)    comment(`  unconditionally go back to loop      ')

label(done)

   print(sum)
   halt

comment(`  start execution at label start  ')

   end(start)
