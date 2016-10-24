#### Learning Assembly (GAS) from C

Using Reverse Engeneer into C to understand how assembly works

The assembly notation used is the x86 [GNU Assembler](http://en.wikipedia.org/wiki/GNU_Assembler) (GAS).

---

A standard "Hello, World!":
```
.globl	_start
 
.text
_start:
	movl	$len, %edx
	movl	$msg, %ecx
	movl	$1, %ebx
	movl	$4, %eax
	int	$0x80
 
	movl	$0, %ebx
	movl	$1, %eax
	int	$0x80
.data
msg:
	.ascii	"Hello, world!\n"
	len =	. - msg
```

To compile:
* On a x86:
```
gcc filename.s -o filename
```
* On a x64:
```
gcc -m32 filename.s -o filename
```
