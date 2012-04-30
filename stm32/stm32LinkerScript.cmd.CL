_estack = 0x20004fff;

MEMORY
{
  ram (rwx) : ORIGIN = 0x20000000, LENGTH = 64K
  rom (rx) : ORIGIN = 0x00000000, LENGTH = 256K
}
SECTIONS
  {
	.  = 0x0;          /* From 0x00000000 */
    .text : {
    *(.isr_vector)      /* Vector table */
    *(.text)        /* Program code */
    *(.text.*)
    *(.rodata)      /* Read only data */
    *(.rodata.*)      /* Read only data */
    } >rom
    
    .gnu.linkonce : {
      *(.gnu.linkonce.t.*)
      *(.gnu.linkonce.r.*)
  } >rom

  .gnu.linkoncearm : {
      *(.gnu.linkonce.armexidx.*)
} >rom

  .rel.text      :
    {
      *(.rel.text)
      *(.rel.text.*)
      *(.rel.gnu.linkonce.t*)
    } >rom
    
    __exidx_start=.;
    .exidx : {
    *(.ARM.exidx*)
     }>rom
    __exidx_end =.;
    
    .extab : {
    *(.ARM.extab*)
    }>rom
    
    .sidat : {
   	 	_etext = .;
	    _sidata = _etext; /* Used by the startup in order to initialize the .data section */
    } >rom
    
        .  = 0x20000000;   /* From 0x20000000 */      
    .data : AT ( _sidata ) {
    . = ALIGN(4);
    _sdata = .;
    *(.data)        /* Data memory */
    . = ALIGN(4);
    _edata = .;
    } >ram

  .bss : {
    . = ALIGN(4);
    _sbss = .;
    *(.bss)         /* Zero-filled run time allocate data memory */
    . = ALIGN(4);
    _ebss = .;
    } >ram
    
    _end = .;
 }  
/*========== end of file ==========*/
