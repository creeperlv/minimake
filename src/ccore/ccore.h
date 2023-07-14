#pragma once
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#ifndef __cplusplus
typedef char bool;
#define false 0
#define true 1
#endif
typedef char *cstr;
bool CStrIsEqual(cstr L, cstr R);
#define null NULL
void WriteLine(cstr str);
void Write(cstr str);
void RequestInput(cstr prompt, cstr *rec);
typedef struct proj_info {
  cstr Name;
  cstr Version;
} ProjectInfo;
typedef struct local_config {
  cstr CCompiler;
  cstr OutputPath;
  cstr InstallPath;
} LocalConfiguration;
void DefaultLC(LocalConfiguration *config);
void WriteLConfig(LocalConfiguration lc, FILE *f);
LocalConfiguration ReadLConfig(FILE *f);
ProjectInfo ReadProjectInfo(FILE *f);
