/*
sielf (s)tripper

(c)Captain_SISka 2007
(r)Rst7
*/
#define MAX_PHNUM	10

#define _CRT_SECURE_CPP_OVERLOAD_STANDARD_NAMES 1
#define _CRT_SECURE_NO_DEPRECATE
#include <stdlib.h>
#include <stdio.h>
#include <iostream>
#include <cstring>
#include <stdint.h>

using namespace std;
#define mfree free


#define hex   ""
#define dec   ""

extern int opt_info;

typedef uint32_t  Elf32_Addr;	//Unsigned program address 4
typedef uint16_t  Elf32_Half;	//Unsigned medium integer  2
typedef uint32_t  Elf32_Off; 	//Unsigned file offset     4
typedef int32_t   Elf32_Sword; 	//Signed large integer     4
typedef uint32_t  Elf32_Word; 	//Unsigned large integer   4

//ELF Header
//e_ident[] Identification Indexes
#define EI_MAG0    0  //File identification
#define EI_MAG1    1  //File identification
#define EI_MAG2    2  //File identification
#define EI_MAG3    3  //File identification
#define EI_CLASS   4  //File class
#define EI_DATA    5  //Data encoding
#define EI_VERSION 6  //File version
#define EI_PAD     7  //Start of padding bytes
#define EI_NIDENT  16 //Size of e_ident[]

typedef struct{
  unsigned char e_ident[EI_NIDENT];
  Elf32_Half e_type;
  Elf32_Half e_machine;
  Elf32_Word e_version;
  Elf32_Addr e_entry;
  Elf32_Off  e_phoff;
  Elf32_Off  e_shoff;
  Elf32_Word e_flags;
  Elf32_Half e_ehsize;
  Elf32_Half e_phentsize;
  Elf32_Half e_phnum;
  Elf32_Half e_shentsize;
  Elf32_Half e_shnum;
  Elf32_Half e_shstrndx;
} Elf32_Ehdr;

#define ET_NONE   0        //No file type
#define ET_REL    1        //Re-locatable file
#define ET_EXEC   2        //Executable file
#define ET_DYN    3        //Shared object file
#define ET_CORE   4        //Core file
#define ET_LOPROC 0xFF00   //Processor-specific
#define ET_HIPROC 0xFFFF   //Processor-specific
#define EM_NONE        0  //No machine
#define EM_M32         1  //AT&T WE 32100
#define EM_SPARC       2  //SPARC
#define EM_386         3  //Intel Architecture
#define EM_68K         4  //Motorola 68000
#define EM_88K         5  //Motorola 88000
#define EM_860         7  //Intel 80860
#define EM_MIPS        8  //MIPS RS3000 Big-Endian
#define EM_MIPS_RS4_BE 10 //MIPS RS4000 Big-Endian
#define EM_ARM         40 //ARM/Thumb Architecture
#define EV_NONE    0 //Invalid version
#define EV_CURRENT 1 //Current version
#define ELFMAG0 0x7f //e_ident[EI_MAG0]
#define ELFMAG1 'E' //e_ident[EI_MAG1]
#define ELFMAG2 'L' //e_ident[EI_MAG2]
#define ELFMAG3 'F' //e_ident[EI_MAG3]
#define ELFCLASSNONE 0 //Invalid class
#define ELFCLASS32   1 //32-bit objects
#define ELFCLASS64   2 //64-bit objects
#define ELFDATANONE 0 //Invalid data encoding
#define ELFDATA2LSB 1 //See Data encodings ELFDATA2LSB, below
#define ELFDATA2MSB 2 //See Data encodings ELFDATA2MSB, below

//Sections
//Section Header
typedef struct{
  Elf32_Word sh_name;
  Elf32_Word sh_type;
  Elf32_Word sh_flags;
  Elf32_Addr sh_addr;
  Elf32_Off  sh_offset;
  Elf32_Word sh_size;
  Elf32_Word sh_link;
  Elf32_Word sh_info;
  Elf32_Word sh_addralign;
  Elf32_Word sh_entsize;
} Elf32_Shdr;

//Special Section Indexes
#define SHN_UNDEF     0
#define SHN_LORESERVE 0xff00
#define SHN_LOPROC    0xff00
#define SHN_HIPROC    0xff1f
#define SHN_ABS       0xfff1
#define SHN_COMMON    0xfff2
#define SHN_HIRESERVE 0xffff

//sh_type
#define SHT_NULL     0
#define SHT_PROGBITS 1
#define SHT_SYMTAB   2
#define SHT_STRTAB   3
#define SHT_RELA     4
#define SHT_HASH     5
#define SHT_DYNAMIC  6
#define SHT_NOTE     7
#define SHT_NOBITS   8
#define SHT_REL      9
#define SHT_SHLIB    10
#define SHT_DYNSYM   11
#define SHT_LOPROC   0x70000000
#define SHT_HIPROC   0x7fffffff
#define SHT_LOUSER   0x80000000
#define SHT_HIUSER   0xffffffff

//Section Attribute Flags, sh_flags
#define SHF_WRITE     1
#define SHF_ALLOC     2
#define SHF_EXECINSTR 4
#define SHF_MASKPROC  0xf0000000

//Program
//Program Header
typedef struct{
  Elf32_Word p_type;
  Elf32_Off p_offset;
  Elf32_Addr p_vaddr;
  Elf32_Addr p_paddr;
  Elf32_Word p_filesz;
  Elf32_Word p_memsz;
  Elf32_Word p_flags;
  Elf32_Word p_align;
} Elf32_Phdr;

//Defined program header flags
#define PF_X 1
#define PF_W 2
#define PF_R 4
#define PF_MASKPROC 0xf0000000

//Segment Types, p_type
#define PT_NULL    0
#define PT_LOAD    1
#define PT_DYNAMIC 2
#define PT_INTERP  3
#define PT_NOTE    4
#define PT_SHLIB   5
#define PT_PHDR    6
#define PT_LOPROC  0x70000000
#define PT_HIPROC  0x7fffffff

//The dynamic section
typedef struct{
  Elf32_Sword d_tag;
  Elf32_Word d_val;
} Elf32_Dyn;

//Dynamic section tags
#define DT_NULL     0
#define DT_NEEDED   1
#define DT_PLTRELSZ 2
#define DT_PLTGOT   3
#define DT_HASH     4
#define DT_STRTAB   5
#define DT_SYMTAB   6
#define DT_RELA     7
#define DT_RELASZ   8
#define DT_RELAENT  9
#define DT_STRSZ    10
#define DT_SYMENT   11
#define DT_INIT     12
#define DT_FINI     13
#define DT_SONAME   14
#define DT_RPATH    15
#define DT_SYMBOLIC 16
#define DT_REL      17
#define DT_RELSZ    18
#define DT_RELENT   19
#define DT_PLTREL   20
#define DT_DEBUG    21
#define DT_TEXTREL  22
#define DT_JMPREL   23
#define DT_BIND_NOW 24
#define DT_LOPROC   0x70000000
#define DT_HIPROC   0x7fffffff

//Relocation Entries
typedef struct{
  Elf32_Addr r_offset;
  Elf32_Word r_info;
} Elf32_Rel;

typedef struct{
  Elf32_Addr  r_offset;
  Elf32_Word  r_info;
  Elf32_Sword r_addend;
} Elf32_Rela;

#define ELF32_R_SYM(i) ((i)>>8)
#define ELF32_R_TYPE(i) ((unsigned char)(i))
#define ELF32_R_INFO(s,t) (((s)<<8)+(unsigned char)(t))

//ARM relocation types
#define R_ARM_NONE            0
#define R_ARM_PC24            1
#define R_ARM_ABS32           2
#define R_ARM_REL32           3
#define R_ARM_PC13            4
#define R_ARM_ABS16           5
#define R_ARM_ABS12           6
#define R_ARM_THM_ABS5        7
#define R_ARM_ABS8            8
#define R_ARM_SBREL32         9
#define R_ARM_THM_PC22        10
#define R_ARM_THM_PC8         11
#define R_ARM_AMP_VCALL9      12
#define R_ARM_SWI24           13
#define R_ARM_THM_SWI8        14
#define R_ARM_XPC25           15
#define R_ARM_THM_XPC22       16
#define R_ARM_COPY            20
#define R_ARM_GLOB_DAT        21
#define R_ARM_JUMP_SLOT       22
#define R_ARM_RELATIVE        23
#define R_ARM_GOTOFF          24
#define R_ARM_GOTPC           25
#define R_ARM_GOT32           26
#define R_ARM_PLT32           27
#define R_ARM_ALU_PCREL_7_0   32
#define R_ARM_ALU_PCREL_15_8  33
#define R_ARM_ALU_PCREL_23_15 34
#define R_ARM_LDR_SBREL_11_0  35
#define R_ARM_ALU_SBREL_19_12 36
#define R_ARM_ALU_SBREL_27_20 37
#define R_ARM_GNU_VTENTRY     100
#define R_ARM_GNU_VTINHERIT   101
#define R_ARM_THM_PC11        102
#define R_ARM_THM_PC9         103
#define R_ARM_RXPC25          249
#define R_ARM_RSBREL32        250
#define R_ARM_THM_RPC22       251
#define R_ARM_RREL32          252
#define R_ARM_RABS32          253
#define R_ARM_RPC24           254
#define R_ARM_RBASE           255

void zeromem_a(void *d, int l){memset(d,0, l);}

//--------------------------------------------------
//only required elf data
Elf32_Ehdr ehdr;	
Elf32_Phdr p[MAX_PHNUM];
int np;
char * pd[MAX_PHNUM];
int oldsz,newsz;
//--------------------------------------------------
int ReadElf(char * filename)
{
  Elf32_Phdr phdrs[MAX_PHNUM];
  Elf32_Word dyn[DT_BIND_NOW+1];
  //char *reloc, *base;
  int n,m;

  zeromem_a(dyn, sizeof(dyn));

  FILE *fin=NULL;
  if ((fin=fopen(filename,"rb"))==NULL) return -1;
  if (fread(&ehdr,sizeof(Elf32_Ehdr),1,fin)!=1) return -2;

    if (ehdr.e_ident[EI_MAG0] != ELFMAG0 ||
        ehdr.e_ident[EI_MAG1] != ELFMAG1 ||
        ehdr.e_ident[EI_MAG2] != ELFMAG2 ||
        ehdr.e_ident[EI_MAG3] != ELFMAG3) {
        cout << "Elf Header not found";
        return -3;
    }

if(opt_info){  cout << "Elf header"<<endl;
  cout << "ehdr.e_entry:"<<ehdr.e_entry<<endl;
  cout << "ehdr.e_phoff:"<<ehdr.e_phoff<<endl;};
  if (ehdr.e_phnum>MAX_PHNUM) return -9;

  for(n=0;n<ehdr.e_phnum;n++)
  		{
	    if (fseek(fin,ehdr.e_phoff+n*ehdr.e_phentsize,SEEK_SET)!=0) return -4;
	    if (fread(&(phdrs[n]),sizeof(Elf32_Phdr),1,fin)!=1) return -5;
	    if (phdrs[n].p_type==PT_LOAD)
       	{
if(opt_info){          cout <<endl;
	       cout << "Program header"<<endl;
		    cout << "Program header"<<endl;
		    cout << "phdr.p_type:"<<phdrs[n].p_type<<endl;
		    cout << "phdr.p_offset:"<<phdrs[n].p_offset<<endl;
		    cout << "phdr.p_vaddr:"<<phdrs[n].p_vaddr<<endl;
		    cout << "phdr.p_paddr:"<<phdrs[n].p_paddr<<endl;
		    cout << "phdr.p_filesz:"<<phdrs[n].p_filesz<<endl;
		    cout << "phdr.p_memsz:"<<phdrs[n].p_memsz<<endl;};
		    }
        };

  np=0;
  for(n=0;n<ehdr.e_phnum;n++)
  	 {
    if (fseek(fin,phdrs[n].p_offset,SEEK_SET)!=0) return -6;
    switch (phdrs[n].p_type)
    		{
		    case PT_LOAD:
           {
				p[np]=phdrs[n];
            pd[np]=(char*)malloc(phdrs[n].p_filesz);
            if (fread((void *)pd[np],1,phdrs[n].p_filesz,fin)!=phdrs[n].p_filesz) return -100-n;
            np++;
		      }
		      break;

    case PT_DYNAMIC:
    			{
			char * dy;
			dy=(char *)malloc(phdrs[n].p_filesz);
			if(opt_info)
				cout << "dyn seg: off="<<hex<<phdrs[n].p_offset<<", sz="<<phdrs[n].p_filesz<<endl;
			if (fread(dy,1,phdrs[n].p_filesz,fin)!=phdrs[n].p_filesz) {mfree(dy); return -8;}

		      m=0;
		      while (((Elf32_Dyn *)dy)[m].d_tag!=DT_NULL)
            	{
					if (((Elf32_Dyn *)dy)[m].d_tag<=DT_BIND_NOW)
               	{
			         if(opt_info){cout<<"d_tag="<<((Elf32_Dyn *)dy)[m].d_tag;
			         cout<<" d_val="<<((Elf32_Dyn *)dy)[m].d_val<<endl;};
  	   			  	dyn[((Elf32_Dyn *)dy)[m].d_tag]=((Elf32_Dyn *)dy)[m].d_val;
		  				}
					m++;
			      }
if(opt_info){ 		      cout << "Dynamic section" << endl;
		      for (m = 0; m <= DT_BIND_NOW; m++)						cout << dec << m <<" = "<< hex << dyn[m]<<endl;
			   cout<<"dyn[DT_REL]="<<dyn[DT_REL]<<", dyn[DT_RELA]="<<dyn[DT_RELA]<<endl;
		      cout<<"dyn[DT_RELSZ]="<<dyn[DT_RELSZ]<<", dyn[DT_RELASZ]="<<dyn[DT_RELASZ]<<endl;};

       if(dyn[DT_RELSZ]!=0)
       		{
            char * reloc=dy+dyn[DT_REL]-phdrs[n].p_vaddr;

			   p[np].p_type=PT_DYNAMIC;
			   p[np].p_vaddr=0;
			   p[np].p_filesz=(sizeof(Elf32_Dyn)*3+dyn[DT_RELSZ]);
			   pd[np]=(char *) malloc(p[np].p_filesz);

			   ((Elf32_Dyn*)pd[np])[0].d_tag=DT_RELSZ;
			   ((Elf32_Dyn*)pd[np])[0].d_val=dyn[DT_RELSZ];

			   ((Elf32_Dyn*)pd[np])[1].d_tag=DT_REL;
			   ((Elf32_Dyn*)pd[np])[1].d_val=sizeof(Elf32_Dyn)*3;

			   ((Elf32_Dyn*)pd[np])[2].d_tag=DT_NULL;

			   memcpy(pd[np]+sizeof(Elf32_Dyn)*3,reloc,dyn[DT_RELSZ]);
			   np++;
            }
	    else
           if(opt_info) cout << "No relocation information dyn[DT_RELSZ]=0" << endl;
      mfree(dy);
      };
      break;

    default:
      return -1000-phdrs[n].p_type;
    }
  }

fseek(fin,0,SEEK_END);
oldsz=ftell(fin);
fclose(fin);
return 0;
};
//--------------------------------------------------
int WriteElf(char * filename)
{
//open file

FILE * f;
if ((f=fopen(filename,"wb"))==NULL) return -1;
//calc phtable offset
int ts=0;
for(int i=0;i<np;i++) ts+=p[i].p_filesz;

//write header
ehdr.e_phnum=np;
ehdr.e_phoff=ts+sizeof(ehdr);
if (fwrite(&ehdr,1,sizeof(ehdr),f)!=sizeof(ehdr)) return -2;

//write sections,edit phtable
int po=sizeof(ehdr);
for(int i=0;i<np;i++)
  {
  if (fwrite(pd[i],1,p[i].p_filesz,f)!=p[i].p_filesz) return -300-i;
  p[i].p_offset=po;
  po+=p[i].p_filesz;
  mfree(pd[i]);
  };
//write table
if (fwrite(&p,1,np*sizeof(Elf32_Phdr),f)!=np*sizeof(Elf32_Phdr)) return -4;
//close
newsz=ftell(f);

fclose(f);
return 0;
};
//--------------------------------------------------

