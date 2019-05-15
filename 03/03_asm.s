  .file "03_asm.s"
  .text
  .globl  decode2
  .type decode2, @function
decode2:
  subq  %rdx, %rsi
  imulq %rsi, %rdi
  movq  %rsi, %rax
  salq  $63, %rax
  sarq  $63, %rax
  xorq  %rdi, %rax
  ret
