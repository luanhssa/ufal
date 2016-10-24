
#### Step 1: Bootloader

* Carrega o kernel no endereço 0x8000

* Entrar no modo protegido

* Jump para o kernel

#### Step 2: Kernel

* Gerência de memória

** Carregar GDT

** Carregar IDT

** Criar segmento

** Loop

