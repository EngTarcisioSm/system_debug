###################################################################################################################################
                                                    INSTALAÇÃO DA BIBLIOTECA 
###################################################################################################################################

- NO TERMINAL DE COMANDO DE EXECUÇÃO PARA O SCRIPT 
    $ chmod +x install_v4.sh

- NA PASTA ONDE OS ARQUIVOS .c E .h ESTÃO INSTALADOS DIGITE O COMANDO 
    $ ./install_v4

###################################################################################################################################
                                                        UTILIZAÇÃO DA LIB
###################################################################################################################################

- INSIRA O SEGUINTE INCLUDE NO ARQUIVO DA FT OU ARQUIVO c
    #include <dlfcn.h>      //lib c padrão para habilitar uso dinamico de libs

- NA FUNÇÃO QUE DESEJA O DEBUG LOGO APÓS AS DEFINIÇÕES DE VARIAVEIS INSIRA O SEGUINTE TRECHO DE CÓDIGO, ONDE ESTA <USUARIO> SE 
QUISER COLOQUE SEU NOME. ABAIXO É DESCRITO TODAS AS OPÇÕES POSSIVEIS DE USO DA BIBLIOTECA 

//------------------------------------------------
//debug <usuario>
void* libraryHandle;

//int (*printDebug)(char*, const char*, ...);         // iii. imprime [tag] [tempo sistema] [mensagem configurada]
//int (*printDebug)(const char*, ...);                // iv.  imprime [tempo sistema] [mensagem configurada]
//int (*printDebug)(char*, const char*, ...);         // v.   imprime [tag] [mensagem configurada]
//int (*printDebug)(const char*, ...);                // vi.  imprime [mensagem configurada]

libraryHandle = dlopen("libsystem_log.so", RTLD_LAZY);
if(!libraryHandle); //sem checagem de verificação

//printDebug = dlsym(libraryHandle, "iSYSTEMLOG_PrintLogFULL");                         // iii.
//printDebug = dlsym(libraryHandle, "iSYSTEMLOG_PrintLogWithoutTag");                   // iv.
//printDebug = dlsym(libraryHandle, "iSYSTEMLOG_PrintLogWithoutTime");                  // v.
//printDebug = dlsym(libraryHandle, "iSYSTEMLOG_PrintLogOnlyString");                   // vi.
if(!printDebug);  //sem checagem de verificação
//------------------------------------------------

- NO TRECHO EM QUE DESEJA DEBUG UTILIZE O SEGUINTE CÓDIGO, O SEGUNDO PARAMETRO É O PADRÃO DE STRING QUE SE DESEJA SER IMPRESSO, 
O TERCEIRO PARAMETRO EM DIANTE SÃO TODAS AS VARIAVEIS QUE SERÃO UTILIZADAS NO DEBUG NA ORDEM EM QUE FOI ESTRUTURADO NO SEGUNDO 
PARAMETRO  

//------------------------------------------------
printDebug("Configure sua string aqui igual a funcao sprintf", <variaveis>);            //iv. e vi.
printDebug("tag", "Configure sua string aqui igual a funcao sprintf", <variaveis>);     //iii. e v.
//------------------------------------------------

- Ao final da função insira o seguinte código 

//------------------------------------------------
dlclose(libraryHandle); //colocar isso no final do ultimo debug
//------------------------------------------------
