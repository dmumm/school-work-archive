comment(` Dylan Mumm   ')
comment(` CPSC 2311 004')

bipush(-40) comment(`initial counter')
istore_0

label(loop)

iconst_0
invokevirtual(1)

bipush(9)
iload_0
imul
bipush(5)
idiv
bipush(32)
iadd
istore_1

iconst_1
invokevirtual(2)


iinc(0,10)


bipush(120)
iload_0
isub

ifge(loop)


return
