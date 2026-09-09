global load_page_dir

load_page_dir:
    mov eax, [esp + 4]
    and eax, 0xFFFFF000
    mov cr3, eax
    ret

global enable_paging

enable_paging:
    mov eax, cr0
    or eax, 0x80000000
	mov cr0, eax
	ret
