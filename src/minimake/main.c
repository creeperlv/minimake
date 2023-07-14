#include "../ccore/ccore.h"
#ifndef VERSION
#define VERSION "Unknown"
#endif
void PrintHelp() {
  WriteLine("minimake [operation]");
  WriteLine("");
  WriteLine("Operations:");
  WriteLine("make, build");
  WriteLine("\tBuild the project");
  WriteLine("new");
  WriteLine("\tCreate a new project definition.");
  WriteLine("config,configure");
  WriteLine("\tCreate project scripts and structure with mkcproj.");
  WriteLine("nlconfig,new-local-configure,new-lconfig");
  WriteLine("\tCreate a local configure for local machine that specifies C "
            "compiler, output path and install path.");
}
void About() {
  WriteLine("minimake");
  Write("Version:");
  WriteLine(VERSION);
  WriteLine("Copyright (C) 2023 Creeper Lv");
  WriteLine("This program and its source code are distributed under the MIT "
            "License");
}
int main(int c, cstr *v) {
  cstr name = null;
  cstr version = null;
  int operation = 0;
  for (int i = 1; i < c; i++) {
    cstr item = v[i];
    if (CStrIsEqual(item, "make") || CStrIsEqual(item, "build")) {
      operation = 1;
    } else if (CStrIsEqual(item, "install")) {
      operation = 2;
    } else if (CStrIsEqual(item, "new")) {
      operation = 3;
    } else if (CStrIsEqual(item, "config") || CStrIsEqual(item, "configure")) {
      operation = 4;
    } else if (CStrIsEqual(item, "new-lconfig") ||
               CStrIsEqual(item, "nlconfig") ||
               CStrIsEqual(item, "new-local-configure")) {
      operation = 6;
    } else if (CStrIsEqual(item, "help")) {
      operation = 0;
    } else if (CStrIsEqual(item, "-n") || CStrIsEqual(item, "--name")) {
      name = v[i + 1];
      i++;
    } else if (CStrIsEqual(item, "-v") || CStrIsEqual(item, "--version")) {
      version = v[i + 1];
      i++;
    } else if (CStrIsEqual(item, "-v") || CStrIsEqual(item, "--version")) {
      version = v[i + 1];
      i++;
    } else if (CStrIsEqual(item, "-i") || CStrIsEqual(item, "--info")) {
      operation = 5;
    }
  }
  switch (operation) {
  case 0: {
    PrintHelp();
  } break;
  case 1: {
    system("sh scripts/build.sh");
  } break;
  case 2: {
    system("sh scripts/install.sh");
  } break;
  case 3: {
    if (name == null) {
      name = malloc(sizeof(char) * 256);
      RequestInput("Give project a name:", &name);
    }
    if (version == null) {
      version = malloc(sizeof(char) * 256);
      RequestInput("Give project a version:", &version);
    }
    {
      FILE *f = fopen("minimake.mkp", "wb");
      // fputs("", f);
      fprintf(f, "name %s\n", name);
      fprintf(f, "version %s\n", version);
      fclose(f);
      WriteLine("Write project file->minimake.mkp");
    }
  } break;
  case 4: {
    ProjectInfo info;
    {
      FILE *f = fopen("minimake.mkp", "r");
      info = ReadProjectInfo(f);
      fclose(f);
    }
    if (info.Name == null) {
      if (name == null) {
        WriteLine("Project Info Require A Name!");
        return 1;
      }
    } else {
      name = info.Name;
    }
    if (info.Version != null)
      version = info.Version;
    LocalConfiguration LC;
    if (access("mklocal.cfg", F_OK) == -1) {
      DefaultLC(&LC);
    } else {
      FILE *f = fopen("mklocal.cfg", "r");
      LC = ReadLConfig(f);
      fclose(f);
    }
    Write("Name:");
    WriteLine(name);
    Write("Version:");
    WriteLine(version);
    Write("CC:");
    WriteLine(LC.CCompiler);
    Write("Output:");
    WriteLine(LC.OutputPath);
    Write("Install:");
    WriteLine(LC.InstallPath);
    cstr cmd = malloc(sizeof(char) * (256 * 3));
    cstr p0 = "mkcproj ";
    cstr pname = " -n ";
    cstr quate = "\"";
    cstr pversion = " -v ";
    cstr po = " -o ";
    cstr pi = " -i ";
    cstr pcc = " -cc ";
    strcpy(cmd, p0);
    strcat(cmd, pname);
    strcat(cmd, quate);
    strcat(cmd, name);
    strcat(cmd, quate);
    strcat(cmd, pversion);
    strcat(cmd, quate);
    strcat(cmd, version);
    strcat(cmd, quate);
    strcat(cmd, pcc);
    strcat(cmd, quate);
    strcat(cmd, LC.CCompiler);
    strcat(cmd, quate);
    strcat(cmd, po);
    strcat(cmd, quate);
    strcat(cmd, LC.OutputPath);
    strcat(cmd, quate);
    strcat(cmd, pi);
    strcat(cmd, quate);
    strcat(cmd, LC.InstallPath);
    strcat(cmd, quate);
    system(cmd);
  } break;
  case 5:
    About();
    break;
  case 6: {
    LocalConfiguration config;
    DefaultLC(&config);
    {
      FILE *cf = fopen("mklocal.cfg", "wb");
      WriteLConfig(config, cf);
      fclose(cf);
    }
  } break;
  default:
    PrintHelp();
    break;
  }
  return 0;
}
