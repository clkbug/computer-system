  .file "03_asm.s"
  .text
  .globl  decode2
  .type decode2, @function
  .globl  loop
  .type loop, @function
decode2:
  subq  %rdx, %rsi
  imulq %rsi, %rdi
  movq  %rsi, %rax
  salq  $63, %rax
  sarq  $63, %rax
  xorq  %rdi, %rax
  ret

# 03.59
store_prod: # %rdi <- dest, %rsi <- x, %rdx <- y
  movq  %rdx, %rax      # %rax <- %rdx (y)
  cqto                  # %rdx:%rax <- yh:yl
  movq  %rsi, %rcx      # %rcx <- x
  sarq  $63, %rcx       # %rcx <- xh
  imulq %rax, %rcx      # %rcx <- hx * yl
  imulq %rsi, %rdx      # %rdx <- yh * xl
  addq  %rdx, %rcx      # %rcx <- hx * yl + yh * xl
  mulq  %rsi            # %rdx:%rax <- xl * yl
  addq  %rcx, %rdx      # %rdx <- high(xl*yl*+hx*yl+yh*xl
  movq  %rax, (%rdi)    # xh*yhは128bitに収まりきらないので無視
  movq  %rdx, 8(%rdi)   # 
  ret

# 03.60
loop: # %rdi = x, %esi = n
  movl  %esi, %ecx # %ecx = x
  movl  $1, %edx   # %edx = 1
  movl  $0, %eax   # %eax = 0
  jmp   .L2
.L3:
  movq  %rdi, %r8  # %r8 = %rdi
  andq  %rdx, %r8  # %r8 &= %rdx
  orq   %r8, %rax  # %rax |= %r8
  salq  %cl, %rdx  # %rdx <<= %cl
.L2:
  testq %rdx, %rdx # %rdx != 0
  jne   .L3
  rep; ret
