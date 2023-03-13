using UnrealBuildTool;

public class My_UE_cppProject : ModuleRules
{
	public My_UE_cppProject(ReadOnlyTargetRules Target) : base(Target)
	{
		PCHUsage = PCHUsageMode.UseExplicitOrSharedPCHs;
	
		PublicDependencyModuleNames.AddRange(new string[] 
		{ 
			"Core",
			"CoreUObject", 
			"Engine",
			"InputCore",
			"AIModule",
			"GameplayTasks"

		});

		//PrivateDependencyModuleNames.AddRange(new string[] {  });
		PublicIncludePaths.Add(ModuleDirectory);
	}
}
