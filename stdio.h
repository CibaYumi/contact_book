// Arquivo stdio.h.
// Interface da biblioteca stdio.
///////////////////////////////////////////////////////////

#ifndef _STDIO_H
#define _STDIO_H

#define NULL 0
#define EOF  (-1)

///////////////////////////////////////////////////////////
// Seção 1 -- Entrada e saída de bytes (chars)
///////////////////////////////////////////////////////////
                                                            
// A função fgetc lê o próximo byte (se tal existir) do 
// arquivo arq. O byte é interpretado como um unsigned
// char, convertido em int, e em seguida devolvido pela
// função. Se arq terminou (e portanto não tem um próximo
// byte) a função devolve EOF. Uso típico:
// i = fgetc (stdin).

int fgetc (FILE *arq);

                                                            
// Esta função tem o mesmo comportamento que fgetc mas é
// implementada como uma macro. Uso típico:
// i = getc (stdin).

int getc (FILE *arq); 

#define getchar ()  getc (stdin)


// Esta função converte c em um byte e coloca esse byte c
// de volta no arquivo arq de tal modo que ele será lido
// pela próxima chamada de fgetc ou getc. É preciso fazer
// pelo menos uma chamada de fgetc ou getc entre chamadas
// consecutivas de ungetc. Uso típico: ungetc (c, arquivo).

int ungetc (int c, FILE *arq);

 
// Esta função converte c em um byte e escreve o byte no
// arquivo arq. Devolve o byte escrito (convertido em int)
// ou EOF no caso de algum erro. Uso típico: 
// fputc (c, stdout).

int fputc (int c, FILE *arq);


// Mesmo comportamento que fputc, mas é implementada como 
// uma macro. Uso típico: putc (c, stdout).

int putc (int c, FILE *arq);

#define putchar (x) putc ((x), stdout)



///////////////////////////////////////////////////////////
// Seção 2 -- Entrada e saída de strings
///////////////////////////////////////////////////////////


// Lê uma linha de texto do arquivo arq. Mais precisamente,
// lê no máximo n-1 bytes do arquivo arq e armazena-os no
// vetor s. (Se algum dos bytes lidos for \0, os resultados
// são imprevisíveis!) A leitura é interrompida se o
// arquivo terminar ou um byte \n for encontrado; nesse
// último caso, o byte \n é armazenado no vetor s. A menos
// que ocorra algum erro, a função armazena um byte \0 em s
// depois do último byte lido de arq. A função devolve s a
// menos que o arquivo tenha terminado ou algum erro tenha
// ocorrido, caso em que devolve NULL. Uso típico:
// fgets (s, n, stdin);

char *fgets (char *s, int n, FILE *arq);


// Recebe uma string str (com byte final \0) e grava essa
// string no arquivo arq. O byte \0 não é gravado. Devolve
// EOF se ocorrer algum erro e devolve um inteiro positivo
// em caso contrário. Uso típico: fputs (s, stdout);

int fputs (char *str, FILE *arq);



///////////////////////////////////////////////////////////
// Seção 3 -- Entrada e saída com formato
///////////////////////////////////////////////////////////

int printf (char *, ...);
int fprintf (FILE *, char *, ...);
int sprintf (char *, char *, ...);

int scanf (char *, ...);
int fscanf (FILE *, char *, ...);
int sscanf (char *, char *, ...);


///////////////////////////////////////////////////////////
// Seção 4 -- Arquivos (files) 
///////////////////////////////////////////////////////////

typedef struct {
   int            _cnt;  // available characters in buffer
   unsigned char *_ptr;  // next char from/to in buffer
   unsigned char *_base; // the buffer
   unsigned char  _flag; // the state of the stream
   unsigned char  _file; // UNIX System file descriptor
   . . .
} FILE;


// Uso típico: arq = fopen ("dir/meuarquivog.txt", "r").

FILE *fopen (char *path, char *mode);


// Uso típico: fclose (arq).

int fclose (FILE *arq);

#endif
