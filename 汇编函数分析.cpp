int main() {
00B61400  push        ebp 
00B61401  mov         ebp,esp  
00B61403  sub         esp,0C0h  // esp指向栈顶
00B61409  push        ebx  
00B6140A  push        esi  
00B6140B  push        edi  
00B6140C  lea         edi,[ebp-0C0h]  
00B61412  mov         ecx,30h  //C0h 除以4，就是30h，因为rep stos用的是dword
00B61417  mov         eax,0CCCCCCCCh  //设置返回值为默认值：无效
00B6141C  rep stos    dword ptr es:[edi]  
    fun(0x8899,0x1100);
00B6141E  push        1100h  //参数压栈，这里遵循__cdecl调用规范，参数由右向左
00B61423  push        8899h  //压栈，此时查看esp地址所在的memory，可以看到两个参数的值
00B61428  call        @ILT+470(_fun) (0B611DBh)  // push 00B6142D, 堆栈清空指令，也就是函数返回后要执行的指令
00B6142D  add         esp,8  //被调用函数的堆栈由主调函数来清空

    return 0;
00B61430  xor         eax,eax  
}
00B61432  pop         edi  
00B61433  pop         esi  
00B61434  pop         ebx  
00B61435  add         esp,0C0h  
00B6143B  cmp         ebp,esp  
00B6143D  call        @ILT+305(__RTC_CheckEsp) (0B61136h)  
00B61442  mov         esp,ebp  
00B61444  pop         ebp  
00B61445  ret  




int fun(int a, int b) {
00B62F90  push        ebp   // 此时查看esp，可以看到主调函数的下一条指令地址：00B6142D  
00B62F91  mov         ebp,esp  //调用函数通常的做法，通过ebp基址寄存器来操作堆//栈数据
00B62F93  sub         esp,14Ch   //为什么是14ch（不是因为堆栈保护，防止缓冲区overflow，而是DEBUG选项造成的）
00B62F99  push        ebx  
00B62F9A  push        esi  
00B62F9B  push        edi  
00B62F9C  lea         edi,[ebp-14Ch]  
00B62FA2  mov         ecx,53h  
00B62FA7  mov         eax,0CCCCCCCCh  
00B62FAC  rep stos    dword ptr es:[edi] //用0CCCCCCCCh初始化堆栈
00B62FAE  mov         eax,dword ptr [___security_cookie (0B6702Ch)]  
00B62FB3  xor         eax,ebp  
00B62FB5  mov         dword ptr [ebp-4],eax  
    char var[128] = "A";
00B62FB8  mov         ax,word ptr [string "A" (0B6573Ch)]  //
00B62FBE  mov         word ptr [ebp-88h],ax  //80h也就是128，写了一个字
00B62FC5  push        7Eh  
00B62FC7  push        0  
00B62FC9  lea         eax,[ebp-86h]  
00B62FCF  push        eax  
00B62FD0  call        @ILT+465(_memset) (0B611D6h)  //通过memset设置
00B62FD5  add         esp,0Ch  
    a = 0x4455;
00B62FD8  mov         dword ptr [ebp+8],4455h  
    b = 0x6677;
00B62FDF  mov         dword ptr [ebp+0Ch],6677h  
    return a + b;
00B62FE6  mov         eax,dword ptr [ebp+8]  
00B62FE9  add         eax,dword ptr [ebp+0Ch] //返回值通过eax保存
}
00B62FEC  push        edx  
00B62FED  mov         ecx,ebp  
00B62FEF  push        eax  
00B62FF0  lea         edx,[ (0B6301Ch)]  
00B62FF6  call        @ILT+125(@_RTC_CheckStackVars@8) (0B61082h)  
00B62FFB  pop         eax  
00B62FFC  pop         edx  
00B62FFD  pop         edi  
00B62FFE  pop         esi  
00B62FFF  pop         ebx   //弹栈？
00B63000  mov         ecx,dword ptr [ebp-4]  
00B63003  xor         ecx,ebp  
00B63005  call        @ILT+15(@__security_check_cookie@4) (0B61014h)  
00B6300A  add         esp,14Ch  
00B63010  cmp         ebp,esp  
00B63012  call        @ILT+305(__RTC_CheckEsp) (0B61136h)  
00B63017  mov         esp,ebp  
00B63019  pop         ebp  //恢复ebp寄存器, ebp中是下一指令加两个参数
00B6301A  ret   // pop EIP, 将主调函数下一个指令放入EIP：00B6142D,
