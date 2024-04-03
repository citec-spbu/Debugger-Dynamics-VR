using UnrealBuildTool;

public class IODebug: ModuleRules
{
        public IODebug(ReadOnlyTargetRules Target) : base(Target)
        {
                PCHUsage = PCHUsageMode.UseExplicitOrSharedPCHs;

                PrivateDependencyModuleNames.AddRange(new string[] {"Core", "CoreUObject", "Engine"});
        
	    }
}