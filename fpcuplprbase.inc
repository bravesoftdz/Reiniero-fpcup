procedure WriteVersion;
begin
  writeln('Version: based on commit fpcup'+RevisionStr+' ('+versiondate+')');
  writeln('Build date: '+{$INCLUDE %DATE%}+' '+{$INCLUDE %TIME%});
  writeln('Compiled for CPU: '+lowercase({$INCLUDE %FPCTARGETCPU%})+' on '+lowercase({$INCLUDE %FPCTARGETOS%}));
  writeln('');
  {$IFDEF DEBUG}
  writeln('*** DEBUG BUILD ***');
  writeln('');
  {$ENDIF}
end;

procedure WriteHelp(ModuleList,ModuleEnabledList:TStringList);
var
  i:integer;
  SortedModules: TStringList;
begin
  writeln('DON''T PANIC!');
  writeln('Everything below is optional...');
  writeln('');
  writeln('fpcup can work with modules - see "only", "include", "skip" below');
  writeln('List of all modules:');
  SortedModules:=TStringList.Create;
  try
    SortedModules.Sorted:=true;
    SortedModules.AddStrings(ModuleList);
    for i:=0 to SortedModules.Count-1 do
      begin
      writeln(SortedModules[i]);
      end;
  finally
    SortedModules.Free;
  end;
  writeln('');
  writeln('The following modules run by default:');
  For i:=0 to ModuleEnabledList.Count-1 do
    begin
    writeln(ModuleEnabledList[i]);
    end;
  writeln('');
  writeln('fpcup --<option> --<option>...');
  writeln('');
  writeln('Options are not required; they include:');
  writeln(' help                  Show this text');
  writeln('');
  writeln(' fpcURL=<URL>          SVN URL from which to download; default: 3.0.0:');
  writeln('                       http://svn.freepascal.org/svn/fpc/branches/3_0_0');
  writeln('                       Accepts shortcuts: ');
  writeln('                       '+installerUniversal.GetAlias('fpcURL','list'));
  {$ifndef FPCONLY}
  writeln(' lazURL=<URL>          SVN URL from which to download; default: 1.6');
  writeln('                       trunk (newest version):');
  writeln('                       http://svn.freepascal.org/svn/lazarus/trunk');
  writeln('                       Accepts shortcuts: ');
  writeln('                       '+installerUniversal.GetAlias('lazURL','list'));
  {$endif}
  writeln(' cputarget=<name>      CPU target for cross_compiling.');
  writeln('                       <name> has to be one of the following:');
  writeln('                       i386,m68k,alpha,powerpc,powerpc64,');
  writeln('                       armeb,arm,sparc,x86_64,ia64');
  writeln(' ostarget=<name>       OS target for cross-compiling.');
  writeln('                       <name> has to be one of the following:');
  writeln('                       darwin,freebsd,linux,netbsd,openbsd,os2,');
  writeln('                       solaris,wince,win32,win64');
  writeln(' subarch=<name>        Subarch target for cross-compiling embedded target.');
  writeln('                       <name> has to be one of the following:');
  writeln('                       armv7m (for Cortex M3),armv7em (for Teensy),armv4,');
  writeln(' fpcOPT=<options>      Options passed on to the FPC make as OPT=options.');
  writeln('                       E.g.: --fpcOPT="-gl -dSAX_HTML_DEBUG -dUSE_MINGW_GDB"');
  writeln(' crossOPT=<options>    Options to be passed to the cross compiler.');
  writeln('                       Corresponds to the CROSSOPT argument in make');
  writeln('                       crosscompiler.');
  writeln('                       E.g. --crossOPT="-CpARMV7 -CfVFPV3" for ARM');
  writeln(' crossbindir=<dir>     Directory where crosscompile toolchain can be found.');
  writeln('                       If target is non-win, fpcup will look for as.');
  writeln('                       If not defined, fpcup tries to find the corect chain.');
  writeln(' crosslibdir=<dir>     Directory where crosscompile libraries can be found.');
  writeln('                       If target is non-win, fpcup will look for libc.so.');
  writeln('                       If not defined, fpcup tries to find the correct library.');
  {$ifndef FPCONLY}
  writeln(' lazOPT=<options>      Options passed on to the Lazarus make as OPT=options.');
  writeln(' lclplatform=<name>    LCL widget set. <name> has to be one of the following:');
  writeln('                       carbon,fpgui,gtk,gtk2,qt,win32,wince');
  {$endif}
  writeln(' installdir=<dir>      Base installation dir. Leads to these subdirs:');
  {$ifndef FPCONLY}
  writeln('                       <dir>\config_lazarus\ Lazarus primary config path');
  {$endif}
  writeln('                       <dir>\cross\          crosscompiling bins/libs');
  writeln('                       <dir>\extras\         extra modules');
  writeln('                       <dir>\fpc\            FPC');
  writeln('                       <dir>\fpcbootstrap\   (Windows) bootstrap compiler+utils');
  {$ifndef FPCONLY}
  writeln('                       <dir>\installerlazwin (Windows) generated installer if');
  writeln('                                             using module installerlazwin');
  writeln('                       <dir>\lazarus\        Lazarus');
  writeln('                       See fpcdir, lazdir, fpcbootstrapdir, binutilsdir');
  writeln('                       primary-config-path');
  {$else}
  writeln('                       See fpcdir, fpcbootstrapdir, binutilsdir');
  {$endif}
  writeln('                       for the defaults when installdir is not specified.');
  writeln('                       You can also use these to override the defaults given');
  writeln('                       by installdir.');
  writeln(' fpcdir=<dir>          Target FPC dir, default c:\development\fpc\');
  writeln('                       or ~\fpc\');
  {$ifndef FPCONLY}
  writeln(' lazdir=<dir>          Target Lazarus dir, default c:\development\lazarus\');
  writeln('                       or ~\lazarus\');
  {$endif}
  writeln(' fpcbootstrapdir=<dir> An existing FPC compiler is needed to compile the FPC');
  writeln('                       sources. Specify location with this option; if no');
  writeln('                       compiler found here, FPCUp will download one there.');
  writeln('                       Make sure it is not in the fpcdir directory');
  writeln('                       Default: c:\development\fpcbootstrap\');
  writeln('                       or ~\fpcbootstrap\');
  writeln(' binutilsdir=<dir>     Windows only:');
  writeln('                       Directory where make, patch etc');
  writeln('                       (the binutils) are located. If make does not');
  writeln('                       exist, binutils will be downloaded there.');
  writeln('                       Default c:\development\fpcbootstrap\');
  writeln('                       Note: the binutils are copied to the');
  writeln('                       FPC directory for use by FPC. This gives');
  writeln('                       a more standard FPC environment.');
  writeln('                       Make sure it is not in the fpcdir directory');
  {$ifndef FPCONLY}
  writeln(' primary-config-path=<dir>');
  writeln('                       Analogous to Lazarus primary-config-path (pcp) parameter.');
  writeln('                       Determines where fpcup will create or use as primary');
  writeln('                       configuration path for the Lazarus it installs/updates.');
  writeln('                       Default: empty (=an OS dependent configuration');
  writeln('                       path is used). However, if installdir is specified,');
  writeln('                       the pcp path will be below it.');
  {$endif}
  writeln(' fpcrevision=<number>  Revert to FPC SVN revision <number>');
  {$ifndef FPCONLY}
  writeln(' lazrevision=<number>  Revert to Lazarus SVN revision <number>');
  {$endif}
  writeln(' httpproxy=<username:password@host:port> username, password: optional');
  writeln(' httpproxy=<http://username:password@host:port> username, password: optional');
  writeln('                       Use HTTP proxy for http downloads,');
  writeln('                       svn over http, hg over http (but not git over http)');
  writeln('                       On Unix/Linux: if the http_proxy environment variable');
  writeln('                       is set, this option is automatically filled in.');
  writeln(' moduleconfig=<file>   Load external module definition file from <file>.');
  writeln('                       Default: '+CONFIGFILENAME+' in the program directory.');
  writeln(' inifile=<file>        Reads in ini file with options.');
  writeln('                       Example ini file: see '+SETTTINGSFILENAME);
  writeln('                       Options can be overwritten by command line parameters.');
  writeln(' inisection=<sec>      Section name to be used if an ini file is specified.');
  writeln('                       If not given, use [General]');
  writeln(' keeplocalchanges      Keep locally modified files (normally these would be');
  writeln('                       backed up as .diff files before doing svn revert.');
  writeln(' reapplylocalchanges   Back up locally modified files into .diff file and');
  writeln('                       reapply the diff with patch or command specified in ');
  writeln('                       parameter patchcmd.');
  writeln(' fpcuplinkname=<name>  Name of the shortcut to the fpcup script.');
  writeln('                       On Windows: a desktop shortcut.');
  writeln('                       On other systems: a shell script in your home directory.');
  writeln('                       If empty specified, no shortcut will be produced.');
  writeln('                       Default: fpcup_update');
  writeln('                         or <lazlinkname>_update if lazlinkname specified');
  {$ifndef FPCONLY}
  writeln(' lazlinkname=<name>    Name of the shortcut to the Lazarus install.');
  writeln('                       On Windows: a desktop shortcut.');
  writeln('                       On other systems: a shell script in your home directory.');
  writeln('                       If empty specified, no shortcut will be produced.');
  writeln('                       Default: depends on Lazarus directory');
  {$endif}
  writeln(' include=<values>      Update/build or clean the modules specified as well ');
  writeln('                       as the default ones.');
  writeln('                       The module list is separated by commas.');
  writeln('                       See above for a list of modules.');
  writeln(' only=<values>         Update/build or clean only the modules specified.');
  writeln('                       The module list is separated by commas.');
  writeln('                       See above for a list of modules.');
  writeln(' skip=<values>         Do not update/build or clean specified modules.');
  writeln('                       The module list is separated by commas.');
  writeln('                       See above for a list of modules.');
  writeln(' fpcPATCH=<values>     Patch the FPC source with the specified patches.');
  writeln('                       The patch list is separated by commas.');
  writeln('                       E.g. --patch="fpcrtti.patch".');
  {$ifndef FPCONLY}
  writeln(' lazPATCH=<values>     Patch the Lazarus source with the specified patches.');
  writeln('                       The patch list is separated by commas.');
  writeln('                       E.g. --patch="docmanager.patch".');
  {$endif}
  writeln(' clean                 Remove files created with build. ');
  writeln('                       Can be combined with skip and only options.');
  writeln(' svnexe=<path>         Full path to svn executable (handy if you have');
  writeln('                       multiple versions.');
  writeln(' patchcmd              Command to use to reapply local changes backed up with');
  writeln('                       svn diff command. The diff file is passed as the only');
  writeln('                       parameter. Add any extra paremeters needed.');
  writeln('                       Default: "patch" ');
  writeln(' uninstall             Uninstall sources and all generated files');
  writeln('                       If no skip/only options given:');
  {$ifndef FPCONLY}
  writeln('                       DELETE entire Lazarus/FPC directories');
  {$else}
  writeln('                       DELETE entire FPC directories');
  {$endif}
  writeln('                       Else: uninstall only certain modules.');
  writeln(' logfilename=<file>    Location of log file. If nothing specified,');
  writeln('                       fpcup.log in the current directory.');
  writeln(' getfullrepo           Get full repositories (enabled by default, so a dummy).');
  writeln('                       Depreciated, still here for backward compatibility');
  writeln(' getfilesonly          Just get files. No repos. Uses "svn export"');
  writeln(' disablejobs           Do not use (parallel) jobs when building FPC.');
  writeln(' usewget               Use wget on Linux as downloader.');
  writeln(' fpcsplit              Use different directory for source and binaries.');
  writeln(' noconfirm             No confirmation asked. For batch operation.');
  writeln(' verbose               Show output from svn and make.');
  writeln(' version               Show version info and quit.');
  writeln('');
  writeln('Share and enjoy!');
  writeln('');
end;

procedure ShowErrorHints();
begin
  writeln('Please check log for details. Possible troubleshooting steps:');
  writeln('First action :');
  writeln('Run fpcup again with --verbose and check for make, lazbuild errors etc.');
  writeln('Run fpcup again also in case of incomple download due to SVN errors.');
  writeln;
  {$IFNDEF MSWINDOWS}
  writeln('- make sure there''s a valid SVN executable in your path.');
  writeln('- make sure the GNU binutils (make etc), windres, subversion client are installed');
  writeln('  e.g. on Debian/Ubuntu: aptitude install build-essential mingw32-binutils subversion ');
  writeln('  ln -s /usr/bin/i586-mingw32msvc-windres /usr/bin/windres');
  writeln('  see http://wiki.lazarus.freepascal.org/Lazarus_Resources#Checking_you_have_windres');
  {$ENDIF MSWINDOWS}
  writeln('If that does not work ... last resort action :');
  writeln('Remove all files from install-directory, and try again');
end;
