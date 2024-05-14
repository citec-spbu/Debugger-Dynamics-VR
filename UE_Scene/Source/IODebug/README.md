# Модуль для UE5 для создания динамического поведения
## Включение в проект

### 1 - Добавит папку с модулем в Source проекта
### 2 - Добавить в конфигурации сборки
Добавить код в Source/<YourProjectEditor.Target.cs, YourProject.Target.cs> (В оба файла)
```
using UnrealBuildTool;
using System.Collections.Generic;

public class YourProjectTarget : TargetRules
{
	public YourProjectTarget(TargetInfo Target) : base(Target)
	{
		...
        ExtraModuleNames.Add("IODebug");  // Add module to 
        ... 
    }
}
```
### 3 - Добавить в зависимости проекта
Добавить код в Source/YourProject/YourProject.Build.cs
```
using UnrealBuildTool;

public class HomeProject : ModuleRules
{
	public HomeProject(ReadOnlyTargetRules Target) : base(Target)
	{
		...
		PublicDependencyModuleNames.AddRange(new string[] { "IODebug" }); // Добавляем зависимость от модуля нашему проекту
        ...
    }
}
```
### 3 - Добавить включение в .uproject
```
{
	"FileVersion": 3,
	"EngineAssociation": "5.3",
	"Category": "",
	"Description": "",
	"Modules": [
		{
			"Name": "YourProject",
			"Type": "Runtime",
			"LoadingPhase": "Default",
			"AdditionalDependencies": [
				"Engine"
			]
		},
        // Включаем наш модуль в проект
		{
			"Name": "IODebug",
			"Type": "Runtime",
			"LoadingPhase": "Default",
			"AdditionalDependencies": [
				"Engine"
			]
		}
        // ---------------------------
	]
    ....
}
```
После правой кнопкой по .uproject жмём Generate Visual Studio project files
### Если возникли ошибки при генерации или при окончательной сборке проекта, внимательно проверьте правильность выполнения всех шагов.
 
## Использование
### * Запись данных происходит в файлы input.txt и output.txt в Content/Developers/...
### * Для работы с модулем используется IOBehaviorComponent.
Первым делом необходимо добавить данный компонент к Actor и установить поля ParamName и Value(Первоначальное значение параметра).
### * Event
У каждого компонента есть Event - On Param Change, который вызывается при поступлении данных в input.txt.
С его помощью можно отслеживать обновление параметров с внешней стороны.
### * Function
Для обновления параметра используется функция UpdateParam. Её можно вызвать обратившись в переменной компонента. Она записывает обновлённое значение в output.txt.

