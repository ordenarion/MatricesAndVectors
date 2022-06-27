import vectors_and_matrices as vm

a = vm.rand_vector(4, -1, 1)

print("a = vm.rand_vector(4, -1, 1)\nb = vm.VxR(a, 10)")
a.print()
b = vm.VxR(a, 10)
b.print()
print("\nvm.VplusV(a, b).print()")
vm.VplusV(a, b).print()

a = vm.rand_vector(3, -1, 1)
b = vm.rand_vector(3, -1, 1)
print("\na = vm.rand_vector(3, -1, 1)\nb = vm.rand_vector(3, -1, 1)")
print("vm.VxV(a, b).print()")
vm.VxV(a, b).print()

c = vm.rand_matrix(5, 6, -3, 4)
d = vm.rand_matrix(5, 6, -3, 4)
print("c = vm.rand_matrix(5, 6, -3, 4)\nd = vm.rand_matrix(5, 6, -3, 4)")
c.print()
d.print()
print("vm.MplusM(c, d).print()")
vm.MplusM(c, d).print()
print("vm.MxR(c, 3).print()")
vm.MxR(c, 3).print()

print("\nc = vm.rand_matrix(2, 6, -3, 4)\nd = vm.rand_matrix(6, 2, -3, 4)")
c = vm.rand_matrix(2, 6, -3, 4)
d = vm.rand_matrix(6, 2, -3, 4)
print("vm.MxM(c, d).print()")
vm.MxM(c, d).print()

print("\nv = vm.rand_vector(3, -1, 1)")
v = vm.rand_vector(3, -1, 1)
v.print()
print("rot = vm.MRot(v, -3.14/4)")
rot = vm.MRot(v, -3.14/4)
rot.print()

