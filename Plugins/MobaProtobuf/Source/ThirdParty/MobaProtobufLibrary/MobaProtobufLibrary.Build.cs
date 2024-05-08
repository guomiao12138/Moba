using UnrealBuildTool;
using System.IO;

public class MobaProtobufLibrary : ModuleRules
{
	public MobaProtobufLibrary(ReadOnlyTargetRules Target) : base(Target)
	{
		Type = ModuleType.External;
		
		PublicSystemLibraryPaths.Add(Path.Combine(ModuleDirectory, "lib"));
		
		PublicIncludePaths.Add(Path.Combine(ModuleDirectory, "include"));
		
		PublicSystemLibraries.Add("libprotobuf.lib");
		PublicSystemLibraries.Add("libprotoc.lib");
	}
}