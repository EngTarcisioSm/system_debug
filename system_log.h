
#include <stdio.h>
#include <string.h>
#include <dirent.h>
#include <unistd.h>
#include <sys/stat.h>
#include <time.h>
#include <stdarg.h>
#include <stdlib.h>
#include <pwd.h>


#ifndef __SYSTEM_LOG_H__
#define __SYSTEM_LOG_H__

#define SYSTEMLOG_NAME_DIR      "log"


/**
 * @brief Imprime no arquivo "/home/user/log/log.txt" uma string configurada
 * 
 * @param Tag tag desejada do logo em formato string
 * @param format padrão de string a ser impressa no arquivo de logs
 * @param ... conteudo variaveis a ser impressos segundo padrão de format
 * @return int 
 *              0: impresso com sucesso
 *              valores menores que zero ou maiores que zero indicam erro
 */
int iSYSTEMLOG_PrintLogFULL(char *Tag, const char* format, ...);

/**
 * @brief Imprime no arquivo "/home/user/log/log.txt" uma string configurada
 * padronizada por format e com os parametros passados
 * 
 * @param Tag tag desejada do logo em formato string
 * @param format padrão de string a ser impressa no arquivo de logs
 * @param ... conteudo variaveis a ser impressos segundo padrão de format
 * @return int 
 *              0: impresso com sucesso
 *              valores menores que zero ou maiores que zero indicam erro
 */
int iSYSTEMLOG_PrintLogWithoutTag(const char* format, ...);

/**
 * @brief Imprime no arquivo "/home/user/log/log.txt" uma string configurada
 * padronizada por format e com os parametros passados
 * 
 * @param Tag tag desejada do logo em formato string
 * @param format padrão de string a ser impressa no arquivo de logs
 * @param ... conteudo variaveis a ser impressos segundo padrão de format
 * @return int 
 *              0: impresso com sucesso
 *              valores menores que zero ou maiores que zero indicam erro
 */
int iSYSTEMLOG_PrintLogWithoutTime(char *Tag, const char* format, ...);

/**
 * @brief Imprime no arquivo "/home/user/log/log.txt" uma string configurada
 * 
 * @param format padrão de string a ser impressa no arquivo de logs
 * @param ... conteudo variaveis a ser impressos segundo padrão de format
 * @return int 
 *              0: impresso com sucesso
 *              valores menores que zero ou maiores que zero indicam erro
 */
int iSYSTEMLOG_PrintLogOnlyString(const char* format, ...);

/**
 * @brief Efetua apenas um teste de linkagem  
 */
void vSYSTEMLOG_PrintTest(void);

#endif