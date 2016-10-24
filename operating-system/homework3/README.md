
#### Step 1: Bootloader

* Carrega o kernel no endereço 0x8200

* Entrar no modo protegido

* Jump para o kernel

#### Step 2: Kernel

* Gerência de memória

** Carregar GDT

** Criar segmento

** Loop

#### Obs:

* Não deve haver vínculo entre o código bootloader e o kernel

* Definir as seguintes funções

** gdt_load : (ponteiro para tabela)

** gdt_init () : [NULL, data, code] segment

** gdt_add_seg : (base, size, ring, type -> seg. de codigo ou de dado)

#### Desafio:

* Carregar o kernel no endereço 1MB
