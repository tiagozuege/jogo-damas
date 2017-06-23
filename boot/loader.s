; Algumas definições para utilização no arquivo.
KERNEL_STACK_SIZE   equ 4096          ; Tamanho da pilha em bytes
MAGIC_NUMBER        equ 0x1BADB002    ; Constante mágica do multiboot
FLAGS               equ 0x0           ; Flags do multiboot
CHECKSUM            equ -MAGIC_NUMBER ; Checksum do multiboot
                                      ; (número mágico + checksum + flags = 0)

; Início da seção text (código). A seção é alinhada em quatro bytes.
section .text
align 4

; Escreve o número mágico, as flags e o checksum no início da seção de código
; para que o multiboot possa identificar o binário corretamente.
dd MAGIC_NUMBER
dd FLAGS
dd CHECKSUM

; Define um símbolo global no binário que será utilizado como ponto de entrada
; identificado no arquivo do linker.
global loader

; Indica que existe uma função externa.
extern _kmain

; Trecho que será executado, carregado pelo linker.
loader:
; Limpa as interrupções.
    cli

; Inicializa a pilha.
    mov esp, kernel_stack

; Chama a função principal do kernel, definida em um arquivo externo.
    call _kmain

; Caso a função principal do kernel termine, desliga o sistema.
    hlt

; Início da seção bss (dados), utilizada para armazenamento dos dados das
; variáveis definidas nos arquivos de código C. O início da pilha é definido
; dentro desta seção e ocupa o tamanho definido por KERNEL_STACK_SIZE.
section .bss
align 4
kernel_stack:

