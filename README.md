![Screenshot](https://braintelligence.io/assets/img/Braintelligence-logo-comp-whtbkg.png "")

**1. Download the Braintelligence-UnrealSDK from GitHub.**

**2. Copy the "Braintelligence" folder into your project's "Source" folder.**

**3. In Windows Explorer, right-click on the .uproject file and select "Generate Visual Studio project files".**
![Screenshot](https://braintelligence.io/assets/sdkimages/02.jpg "")


**4. Now, open the project in Visual Studio. In the Solution Explorer, you should see the "Braintelligence" folder.**
![Screenshot](https://braintelligence.io/assets/sdkimages/01.jpg "")
**5. Open the .uproject file in Visual Studio and add the following code to the modules:**
```json
{
    "Name": "Braintelligence",
    "Type": "Runtime",
    "LoadingPhase": "Default"
}
```
![Screenshot](https://braintelligence.io/assets/sdkimages/03.jpg "")
**6. Open the "ProjectName.Target.cs" file and add the following code to it (see Screenshot 4):**
```csharp
ExtraModuleNames.Add("Braintelligence");
```
![Screenshot](https://braintelligence.io/assets/sdkimages/04.jpg "")
**7. Open the "ProjectNameEditor.Target.cs" file and add the following code to it:**
```csharp
ExtraModuleNames.Add("Braintelligence");
```

**8. Open the project in Unreal Engine by double-clicking the "ProjectName.uproject" file in Windows Explorer or by running the project in Visual Studio.**

**9. In the Unreal Engine Editor, navigate to the Edit menu, go to Project Settings, and find the Plugins section for "Braintelligence." Enter the KEY that you received in your email after registration. If you don't have a Key, you can use "12345".**
![Screenshot](https://braintelligence.io/assets/sdkimages/05.jpg "")
**10. To initialize Braintelligence, open the level's blueprint or any other part of the project suitable for initializing a plugin.**

**11. Add an "Event BeginPlay" node to the blueprint, or use it if it's already added.**

**12. Add the "Initialize" function from Braintelligence to the blueprint and connect it to the "Event BeginPlay".**

**13. Now, everything is ready. Your project will be initialized and connected to the Braintelligence server during project startup. From this point on, you can send events to the Braintelligence server.**

**14. AS AN EXAMPLE, we'll add an event in the following steps. Use the "SendEvent" function whenever something important happens that you want to monitor, such as the user's emotional reaction.**

**15. To ensure there is enough time for the sockets to be created and connected to the server, use a "Delay" function with a 5-second duration.**

**16. After connecting the "Initialize" to the "Delay" function, add a "SendEvent" function and connect it to the "Delay".**

**17. The "SendEvent" function has two parameters: Event Name (a string) and the expected emotion, which can be one of the four predefined emotions or none. Refer to the documentation or contact support for the emotions table.**
![Screenshot](https://braintelligence.io/assets/sdkimages/06.jpg "")
**18. In this example, every time the project starts, after the "Event Begin Play," Braintelligence gets initialized. After a 5-second delay, an event is sent to the Braintelligence local server. You can use the "SendEvent" function in the same way for other important events during gameplay.**
