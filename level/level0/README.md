## Level 0


Running ./level1 without args provokes a segmentation fault. Letter and numbers print a 'No !' in the standard input


``` bash
level0@RainFall:~$ ./level0 11
No !
level0@RainFall:~$ ./level0 bonjour 
No !
```


To inspect what call this program we can use gdb

1. Run program 

``` bash
gdb level1 42
```


2. To dissamble binary use disassemble command 

``` bash

level0@RainFall:~$ gdb level0
GNU gdb (Ubuntu/Linaro 7.4-2012.04-0ubuntu2.1) 7.4-2012.04
Copyright (C) 2012 Free Software Foundation, Inc.
License GPLv3+: GNU GPL version 3 or later <http://gnu.org/licenses/gpl.html>
This is free software: you are free to change and redistribute it.
There is NO WARRANTY, to the extent permitted by law.  Type "show copying"
and "show warranty" for details.
This GDB was configured as "i686-linux-gnu".
For bug reporting instructions, please see:
<http://bugs.launchpad.net/gdb-linaro/>...
Reading symbols from /home/user/level0/level0...(no debugging symbols found)...done.
(gdb) b main
Breakpoint 1 at 0x8048ec3
(gdb) run
Starting program: /home/user/level0/level0 

Breakpoint 1, 0x08048ec3 in main ()
(gdb) disassemble
Dump of assembler code for function main:
   0x08048ec0 <+0>:	push   %ebp #save epb on stack
   0x08048ec1 <+1>:	mov    %esp,%ebp #ebp point on top -> beginning main frame
=> 0x08048ec3 <+3>:	and    $0xfffffff0,%esp #put esp on 16bytes
   0x08048ec6 <+6>:	sub    $0x20,%esp #substract 32 on esp => make space for local variable. Local bc in x86, local variable are below ebp, while the arguments of the function are above 
   0x08048ec9 <+9>:	mov    0xc(%ebp),%eax #put in eax the result of 0xc(%ebp). 0xc(%ebp) = 12(%epb) = epb + 12 = argv. 

#adresse haute
#        ┌─────────────────┐
#ebp+12  │      argv       │  ← 3e chose pushée
#        ├─────────────────┤
#ebp+8   │      argc       │  ← 2e chose pushée
#        ├─────────────────┤
#ebp+4   │  adresse retour │  ← pushée par call
#        ├─────────────────┤
#ebp+0   │    ancien ebp   │  ← pushée par push %ebp
#        └─────────────────┘  ← ebp pointe ici
#adresse basse

   0x08048ecc <+12>:	add    $0x4,%eax # add 4 in eax. Each pointor = 4 octet. Go to argv[1]
   # add something,something = manipulate directly the value of eax (the adress) 
   # mov (something), something = () means go reading to that address on memory
   # add 4 to argv to get argv[1]

   #
   0x08048ecf <+15>:	mov    (%eax),%eax
   #AVANT :
      #eax = 0xbffff234      ← c'est une adresse (&argv[1])
   #En mémoire :
      #0xbffff234  →  [ 0xbffff5a0 ]   ← c'est argv[1] (pointeur vers la string)

   #APRÈS :
   #eax = 0xbffff5a0      ← maintenant eax contient argv[1]

   0x08048ed1 <+17>:	mov    %eax,(%esp) #writing in esp, eax. Push of 1rst arg for atoi 
   0x08048ed4 <+20>:	call   0x8049710 <atoi> #calling atoi with eax value
   0x08048ed9 <+25>:	cmp    $0x1a7,%eax # comp avec 0x1a7, 423 en decimal 
   0x08048ede <+30>:	jne    0x8048f58 <main+152> #jump if not equal
   0x08048ee0 <+32>:	movl   $0x80c5348,(%esp) #mov long 
   0x08048ee7 <+39>:	call   0x8050bf0 <strdup> #call strdup with harcoded string. We know its hardcoded bc we give and adress to strdup, already knew by the compilator, so hardcoded.  
   0x08048eec <+44>:	mov    %eax,0x10(%esp) #get the result of strdup in eax 
   0x08048ef0 <+48>:	movl   $0x0,0x14(%esp) #get in eax a local variable (another one), initialize to zero 
   0x08048ef8 <+56>:	call   0x8054680 <getegid> #calling getegid 
   0x08048efd <+61>:	mov    %eax,0x1c(%esp) #get result 
   0x08048f01 <+65>:	call   0x8054670 <geteuid> #calling
   0x08048f06 <+70>:	mov    %eax,0x18(%esp) #get result 
   0x08048f0a <+74>:	mov    0x1c(%esp),%eax #prepare calling 
   0x08048f0e <+78>:	mov    %eax,0x8(%esp)
   0x08048f12 <+82>:	mov    0x1c(%esp),%eax #get result 
   0x08048f16 <+86>:	mov    %eax,0x4(%esp)
   0x08048f1a <+90>:	mov    0x1c(%esp),%eax
   0x08048f1e <+94>:	mov    %eax,(%esp)
   0x08048f21 <+97>:	call   0x8054700 <setresgid>
   0x08048f26 <+102>:	mov    0x18(%esp),%eax
   0x08048f2a <+106>:	mov    %eax,0x8(%esp)
   0x08048f2e <+110>:	mov    0x18(%esp),%eax
   0x08048f32 <+114>:	mov    %eax,0x4(%esp)
   0x08048f36 <+118>:	mov    0x18(%esp),%eax
   0x08048f3a <+122>:	mov    %eax,(%esp)
   0x08048f3d <+125>:	call   0x8054690 <setresuid>
   0x08048f42 <+130>:	lea    0x10(%esp),%eax
   0x08048f46 <+134>:	mov    %eax,0x4(%esp) 
   0x08048f4a <+138>:	movl   $0x80c5348,(%esp)
   0x08048f51 <+145>:	call   0x8054640 <execv> 
   0x08048f56 <+150>:	jmp    0x8048f80 <main+192>
   0x08048f58 <+152>:	mov    0x80ee170,%eax
   0x08048f5d <+157>:	mov    %eax,%edx
   0x08048f5f <+159>:	mov    $0x80c5350,%eax
   0x08048f64 <+164>:	mov    %edx,0xc(%esp)
   0x08048f68 <+168>:	movl   $0x5,0x8(%esp)
   0x08048f70 <+176>:	movl   $0x1,0x4(%esp)
   0x08048f78 <+184>:	mov    %eax,(%esp)
   0x08048f7b <+187>:	call   0x804a230 <fwrite>
   0x08048f80 <+192>:	mov    $0x0,%eax
   0x08048f85 <+197>:	leave  
   0x08048f86 <+198>:	ret    
End of assembler dump.
(gdb) 
```

### Analyse 



push %ebp        ← sauvegarde l'ancien ebp
mov %esp, %ebp   ← ebp pointe maintenant ici
```

---

Ce qui donne cette structure en mémoire :
```
adresse haute
        ┌─────────────────┐
ebp+12  │      argv       │  ← 3e chose pushée
        ├─────────────────┤
ebp+8   │      argc       │  ← 2e chose pushée
        ├─────────────────┤
ebp+4   │  adresse retour │  ← pushée par call
        ├─────────────────┤
ebp+0   │    ancien ebp   │  ← pushée par push %ebp
        └─────────────────┘  ← ebp pointe ici
adresse basse

