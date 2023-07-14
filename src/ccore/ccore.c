#include "ccore.h"
bool CStrIsEqual(cstr L, cstr R) {
  if (L == null || R == null) {
    if (L == R)
      return true;
    return false;
  }
  int lenL = strlen(L);
  int lenR = strlen(R);
  if (lenL != lenR)
    return false;
  for (int i = 0; i < lenL; i++) {
    if (L[i] != R[i])
      return false;
  }
  return true;
}

void WriteLine(cstr str) { printf("%s\n", str); }
void Write(cstr str) { printf("%s", str); }

void RequestInput(cstr prompt, cstr *rec) {
  printf("%s\n", prompt);
  scanf("%s", rec[0]);
}

void WriteLConfig(LocalConfiguration lc, FILE *f) {
  fprintf(f, "CC %s\n", lc.CCompiler);
  fprintf(f, "Output %s\n", lc.OutputPath);
  fprintf(f, "Install %s\n", lc.InstallPath);
}

LocalConfiguration ReadLConfig(FILE *f) {
  LocalConfiguration lc;

  while (true) {
    cstr item = malloc(sizeof(char) * 256);
    int __read = fscanf(f, "%s", item);
    if (__read == EOF) {
      free(item);
      break;
    }
    if (CStrIsEqual(item, "CC")) {
      lc.CCompiler = malloc(sizeof(char) * 256);
      int __read = fscanf(f, "%s", lc.CCompiler);
      if (__read == EOF) {
        break;
      }
    } else if (CStrIsEqual(item, "Output")) {
      lc.OutputPath = malloc(sizeof(char) * 256);
      int __read = fscanf(f, "%s", lc.OutputPath);
      if (__read == EOF) {
        break;
      }
    } else if (CStrIsEqual(item, "Install")) {
      lc.InstallPath = malloc(sizeof(char) * 256);
      int __read = fscanf(f, "%s", lc.InstallPath);
      if (__read == EOF) {
        break;
      }
    }
    free(item);
  }
  return lc;
}

void DefaultLC(LocalConfiguration *config) {
  config->CCompiler = "gcc";
  config->OutputPath = "bin/";
  config->InstallPath = "/bin/";
}

ProjectInfo ReadProjectInfo(FILE *f) {
  ProjectInfo info;
  info.Version = null;
  info.Name = null;
  while (true) {
    cstr item = malloc(sizeof(char) * 256);
    int __read = fscanf(f, "%s", item);
    if (__read == EOF) {
      free(item);
      break;
    }
    if (CStrIsEqual(item, "name")) {
      info.Name = malloc(sizeof(char) * 256);
      int __read = fscanf(f, "%s", info.Name);
      if (__read == EOF) {
        break;
      }
    } else if (CStrIsEqual(item, "version")) {
      info.Version = malloc(sizeof(char) * 256);
      int __read = fscanf(f, "%s", info.Version);
      if (__read == EOF) {
        break;
      }
    }
    free(item);
  }
  return info;
}
