#include "system_log.h"

/******************************************************************************/

#define SYSTEMLOG_LEN_PATH              1024
#define SYSTEMLOG_LEN_NAME_LINE         256
#define SYSTEMLOG_PERMISSION            0777

#define SYSTEMLOG_ERROR_CHECK_USERNAME                  -1
#define SYSTEMLOG_ERROR_CHECK_OPEN_DIR                  -2
#define SYSTEMLOG_ERROR_CHECK_USERNAME_CREATEDIR        -3
#define SYSTEMLOG_ERROR_CHECK_FAIL_CREATE_DIR           -4
#define SYSTEMLOG_ERROR_CHECK_ACCESS_CREATE_FILE_LOG    -5
#define SYSTEMLOG_ERROR_RANDOM                          -99
/******************************************************************************/

/**
 * @brief Imprime no arquivo "/home/user/log/log.txt" uma string configurada 
 * padronizada por format e com os parametros passados
 * 
 * @param Tag tag desejada do logo em formato string
 * @param cEnableTime habilita (qualquer valor maior que zero) ou desabilita
 * a vizualização de tempo no log (valor = 0)
 * @param format padrão de string a ser impressa no arquivo de logs
 * @param buff conteudo a ser impresso
 * @return int 
 *              0: impresso com sucesso 
 *              valores menores que zero ou maiores que zero indicam erro
 */
int iSYSTEMLOG_PrintLog(char *Tag, char cEnableTime, const char* format, char *buff);

/**
 * @brief Verifica a existencia de determinado diretório
 * 
 * @param ccPathDir diretório a ser verificado sua existencia
 * @return int 
 *              return < 0 : erros de sistema
 *              return == 0: arquivo localizado
 *              return == 1: arquivo não localizado
 *              return > 1 : resposta impossivel
 */
int iSYSTEMLOG_CheckDir(const char * ccPathDir);

/**
 * @brief cria no diretório /home/user/ a pasta log
 * 
 * @return int 
 *              return == -1: não localizou nome de usuário (grave)
 *              return == -2: erro desconhecido (gravissimo)
 *              return == 0 : diretório criado com sucesso
 *              return == 1 : diretório não criado provavelmente ja existente
 */
int iSYSTEMLOG_CreateDirLog(void);

/**
 * @brief Efetua a checagem e criação do arquivo log.txt 
 * 
 * @return int 
 *          -1: erro de sistema 
 *           0: arquivo criado ou já existente
 */
int iSYSTEMLOG_FileLog(void);

/**
 * @brief Captura os dados de tempo do sistema 
 * 
 * @param StringTime ponteiro para o qual as informações de tempo serão 
 * armazenadas
 */
void vSYSTEMLOG_RequestTime(char *StringTime);

/**
 * @brief Imprime a string em um arquivo ja predefinido "/home/user/log/log.txt"
 * 
 * @param String String a ser escrito 
 * @return int 
 *           0: impressão realizada com sucesso
 *          -1: falha na impressão
 *          -2: falha de abertura de arquivo
 */
int vSYSTEMLOG_PrintFile(char *String);
/******************************************************************************/

int iSYSTEMLOG_PrintLogOnlyString(const char* format, ...)
{
    va_list args;
    int iAnswer;
    char* buffer;
    va_start(args, format);

    /**
     * Inclusão do texto de log 
     */
    
    /**
     * Calcula o tamanho necessário para o buffer
     */
    va_start(args, format);
    int size = vsnprintf(NULL, 0, format, args);
    va_end(args);
    buffer = (char*)malloc((size + 1) * sizeof(char));

    /**
     * Formata a string e armazena no buffer
     */
    va_start(args, format);
    vsnprintf(buffer, size + 1, format, args);
    va_end(args);

    iAnswer =  iSYSTEMLOG_PrintLog(NULL, 0, format, buffer);
    free(buffer);
    return iAnswer;
}
//#############################################################################

//#############################################################################
int iSYSTEMLOG_PrintLogWithoutTime(char *Tag, const char* format, ...)
{
    va_list args;
    int iAnswer;
    char* buffer;
    va_start(args, format);

    /**
     * Inclusão do texto de log 
     */
    
    /**
     * Calcula o tamanho necessário para o buffer
     */
    va_start(args, format);
    int size = vsnprintf(NULL, 0, format, args);
    va_end(args);
    buffer = (char*)malloc((size + 1) * sizeof(char));

    /**
     * Formata a string e armazena no buffer
     */
    va_start(args, format);
    vsnprintf(buffer, size + 1, format, args);
    va_end(args);

    iAnswer =  iSYSTEMLOG_PrintLog(NULL, 0, format, buffer);
    free(buffer);
    return iAnswer;
}
//#############################################################################

//#############################################################################
int iSYSTEMLOG_PrintLogWithoutTag(const char* format, ...)
{
    va_list args;
    int iAnswer;
    char* buffer;
    va_start(args, format);

    /**
     * Inclusão do texto de log 
     */
    
    /**
     * Calcula o tamanho necessário para o buffer
     */
    va_start(args, format);
    int size = vsnprintf(NULL, 0, format, args);
    va_end(args);
    buffer = (char*)malloc((size + 1) * sizeof(char));

    /**
     * Formata a string e armazena no buffer
     */
    va_start(args, format);
    vsnprintf(buffer, size + 1, format, args);
    va_end(args);

    iAnswer =  iSYSTEMLOG_PrintLog(NULL, 0, format, buffer);
    free(buffer);
    return iAnswer;
}
//#############################################################################

//#############################################################################
int iSYSTEMLOG_PrintLogFULL(char *Tag, const char* format, ...)
{
    va_list args;
    int iAnswer;
    char* buffer;
    va_start(args, format);

    /**
     * Inclusão do texto de log 
     */
    
    /**
     * Calcula o tamanho necessário para o buffer
     */
    va_start(args, format);
    int size = vsnprintf(NULL, 0, format, args);
    va_end(args);
    buffer = (char*)malloc((size + 1) * sizeof(char));

    /**
     * Formata a string e armazena no buffer
     */
    va_start(args, format);
    vsnprintf(buffer, size + 1, format, args);
    va_end(args);

    iAnswer = iSYSTEMLOG_PrintLog(Tag, 1, format, buffer);
    free(buffer);
    return iAnswer;
}
//#############################################################################

//#############################################################################
int iSYSTEMLOG_PrintLog(char *Tag, char cEnableTime, const char* format, char *buff)
{
    va_list args;
    char message[SYSTEMLOG_LEN_PATH];
    int iAux01, iAux02;
    int iSize;
    
    /**
     * Verificações internas e organização 
     */
    iAux01 = iSYSTEMLOG_CheckDir("log");                                        // Verifica se a pasta log já esta criada

    if(iAux01 == -1 || iAux01 == -2) return iAux01; 
    else if (iAux01 < -2) return SYSTEMLOG_ERROR_RANDOM;  
    else if (iAux01 > 1) return SYSTEMLOG_ERROR_RANDOM;                                                  // erro em sistema
    else if (iAux01 == 1)
    {
        iAux02 = iSYSTEMLOG_CreateDirLog();                                     // Criação do diretório 
        if(iAux02 != 0 || iAux02 != 1) return iAux02;
                                         // algo não permitiu a criação da pasta
        /**
         * resultado esperado 0: criado com sucesso
         * resultado esperado 1: pasta já existente
         */
    }

    /**
     * Checando a existencia ou criação do arquivo log.txt
     */
    iAux01 = iSYSTEMLOG_FileLog();
    if(iAux01 != 0 ) return SYSTEMLOG_ERROR_CHECK_ACCESS_CREATE_FILE_LOG;                                                 // não foi possivel criar o arquivo    
    
    /**
     * Inicio da escrita da mensagem de log 
     */
    memset(message, 0x00, sizeof(message));

    if(Tag != NULL) sprintf(message, "[%s] ", Tag);                             // habilita tag 
    if(cEnableTime != 0) vSYSTEMLOG_RequestTime(message);                       // habilita tempo no log
    

    /**
     * Inclusão do texto de log 
     */
    
    strcat(message, buff);

    vSYSTEMLOG_PrintFile(message);
    return 0;
}

// int iSYSTEMLOG_PrintLog(char *Tag, char cEnableTime, const char* format, ...)
// {
//     va_list args;
//     char message[SYSTEMLOG_LEN_PATH];
//     int iAux01, iAux02;
//     char* buffer;
//     int iSize;
    
//     /**
//      * Verificações internas e organização 
//      */
//     iAux01 = iSYSTEMLOG_CheckDir("log");                                        // Verifica se a pasta log já esta criada

//     if(iAux01 < 0) return -1;                                                   // erro em sistema
//     else if (iAux01 == 1)
//     {
//         iAux02 = iSYSTEMLOG_CreateDirLog();                                     // Criação do diretório 
//         if(iAux02 < 0) return -2;                                               // erro em sistema
//         else if(iAux02 > 1) return 1;                                           // algo não permitiu a criação da pasta
//         /**
//          * resultado esperado 0: criado com sucesso
//          * resultado esperado 1: pasta já existente
//          */
//     }

//     /**
//      * Checando a existencia ou criação do arquivo log.txt
//      */
//     iAux01 = iSYSTEMLOG_FileLog();
//     if(iAux01 != 0 ) return -3;                                                 // não foi possivel criar o arquivo    
    
//     /**
//      * Inicio da escrita da mensagem de log 
//      */
//     memset(message, 0x00, sizeof(message));

//     if(Tag != NULL) sprintf(message, "[%s] ", Tag);                             // habilita tag 
//     if(cEnableTime != 0) vSYSTEMLOG_RequestTime(message);                       // habilita tempo no log
    

//     /**
//      * Inclusão do texto de log 
//      */
    
//     /**
//      * Calcula o tamanho necessário para o buffer
//      */
//     va_start(args, format);
//     int size = vsnprintf(NULL, 0, format, args);
//     va_end(args);
//     buffer = (char*)malloc((size + 1) * sizeof(char));

//     /**
//      * Formata a string e armazena no buffer
//      */
//     va_start(args, format);
//     vsnprintf(buffer, size + 1, format, args);
//     va_end(args);

//     strcat(message, buffer);

//     free(buffer);

//     printf("%d -- %s\n", size, buffer);

//     vSYSTEMLOG_PrintFile(message);
    
//     //printf("%s\n", message);
//     return 0;
// }
//#############################################################################

//#############################################################################
int iSYSTEMLOG_CreateDirLog(void)
{
    char cPath[SYSTEMLOG_LEN_PATH];
    int iResultadoCreateDir = 1;
    char *username = NULL;

    //criação do path da pasta 
    uid_t uid = getuid();
    struct passwd *pw = getpwuid(uid);

    // username = getlogin();
    // if(username == NULL) return SYSTEMLOG_ERROR_CHECK_USERNAME_CREATEDIR;                                             // erro: não localizou nome de usuario
    if (pw == NULL) return SYSTEMLOG_ERROR_CHECK_USERNAME;                                             // erro: não localizou nome de usuario
    username = pw->pw_name;
    
    memset(cPath, 0x00, sizeof(cPath));
    strcat(cPath, "/home/");
    strcat(cPath, username);
    strcat(cPath, "/");
    strcat(cPath, SYSTEMLOG_NAME_DIR);

    //criação do diretório
    iResultadoCreateDir = mkdir(cPath, SYSTEMLOG_PERMISSION);
    
    //resposta ao sistema   
    if((iResultadoCreateDir == 0)) return 0;
    else return -1;

    //erro imprevisivel
    return SYSTEMLOG_ERROR_CHECK_FAIL_CREATE_DIR;
}
//#############################################################################

//#############################################################################
int iSYSTEMLOG_CheckDir(const char * Dir)
{    
    struct dirent *entry;

    char cPath[SYSTEMLOG_LEN_PATH];
    
    // char *username = NULL;
    // username = getlogin();
    // if(username == NULL) return SYSTEMLOG_ERROR_CHECK_USERNAME;                                             // erro: não localizou nome de usuario

    uid_t uid = getuid();
    struct passwd *pw = getpwuid(uid);
    char *username;

    if (pw == NULL) return SYSTEMLOG_ERROR_CHECK_USERNAME;                                             // erro: não localizou nome de usuario
    username = pw->pw_name;


    memset(cPath, 0x00, sizeof(cPath));
    strcat(cPath, "/home/");
    strcat(cPath, username);

    DIR *dir = opendir(cPath);
    if(dir == NULL) return SYSTEMLOG_ERROR_CHECK_OPEN_DIR;                                                  // erro: não encontrar o diretório raiz do usuário

    while((entry = readdir(dir)) != NULL) 
    {
        if(strcmp(entry->d_name, Dir) == 0) return 0;                           // a pasta foi localizada no diretório
    }

    return 1;                                                                   // a pasta não foi localizada no diretório
}
//#############################################################################

//#############################################################################
int iSYSTEMLOG_FileLog(void)
{
    char cPath[SYSTEMLOG_LEN_PATH];
    char *username = NULL;
    FILE *file;

    //criação do path do arquivo 
    uid_t uid = getuid();
    struct passwd *pw = getpwuid(uid);

    if (pw == NULL) return SYSTEMLOG_ERROR_CHECK_USERNAME;                                             // erro: não localizou nome de usuario
    username = pw->pw_name;
    
    // username = getlogin();
    // if(username == NULL) return -1;                                             // erro: não localizou nome de usuario
    
    
    memset(cPath, 0x00, sizeof(cPath));
    strcat(cPath, "/home/");
    strcat(cPath, username);
    strcat(cPath, "/");
    strcat(cPath, SYSTEMLOG_NAME_DIR);
    strcat(cPath, "/");
    strcat(cPath, "log.txt");

    file = fopen(cPath, "a");                                                   // cria o arquivo se ele não existir, se existir não faz nada

    if(file == NULL)
    {
        return -1;
    }
    fclose(file);
    return 0;
}
//#############################################################################

//#############################################################################
void vSYSTEMLOG_RequestTime(char *StringTime)
{
    time_t now;
    struct tm *xInfoTime;
    char aux[50];

    // requesita o tempo atual
    now = time(NULL);

    // Conversão de tempo para estrutura tm 
    xInfoTime = localtime(&now);

    sprintf(
        aux, 
        "[%02d/%02d/%04d - %02d:%02d:%02d] ",
        xInfoTime->tm_mday, 
        xInfoTime->tm_mon + 1, 
        xInfoTime->tm_year + 1900,
        xInfoTime->tm_hour, 
        xInfoTime->tm_min, 
        xInfoTime->tm_sec
    );
    strcat(StringTime, aux);
}
//#############################################################################

//#############################################################################
int vSYSTEMLOG_PrintFile(char *String)
{
    FILE *file;
    char cPath[SYSTEMLOG_LEN_PATH];
    char *username = NULL;
    int iAnswer;

    //criação do path do arquivo 
    uid_t uid = getuid();
    struct passwd *pw = getpwuid(uid);

    if (pw == NULL) return SYSTEMLOG_ERROR_CHECK_USERNAME;                                             // erro: não localizou nome de usuario
    username = pw->pw_name;
    
    // username = getlogin();
    // if(username == NULL) return -1;                                             // erro: não localizou nome de usuario
    memset(cPath, 0x00, sizeof(cPath));
    strcat(cPath, "/home/");
    strcat(cPath, username);
    strcat(cPath, "/");
    strcat(cPath, SYSTEMLOG_NAME_DIR);
    strcat(cPath, "/");
    strcat(cPath, "log.txt");

    file = fopen(cPath, "a");

    if(file == NULL) return -2;                                                 // não foi possivel abrir o arquivo

    iAnswer = fprintf(file, "%s", String);

    if(iAnswer <= 0) return -3;                                                 //não escreveu nada no arquivo 

    // fecha arquivo 
    fclose(file);

}
//#############################################################################

//#############################################################################
void vSYSTEMLOG_PrintTest(void)
{
    printf("Apenas um teste de linkagem\n");
}
//#############################################################################