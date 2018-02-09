#pragma once

#include "ScriptResource.h"

#define SU_IF_ABILITY "Ability"
#define SU_IF_SKILL "Skill"
#define SU_IF_SKILL_MANAGER "SkillManager"
#define SU_IF_SKILL_INDICATORS "SkillIndicators"
#define SU_IF_SKILL_CALLBACK "SkillCallback"
#define SU_IF_NOTETYPE "NoteType"


class ExecutionManager;

class AbilityParameter final {
public:
    std::string Name;
    std::unordered_map<std::string, boost::any> Arguments;
};

class SkillParameter final {
public:
    std::string Name;
    std::string Description;
    std::string IconPath;
    std::vector<AbilityParameter> Abilities;
};

enum class AbilityNoteType {
    Tap = 1,
    ExTap,
    Flick,
    Air,
    HellTap,
    Hold,
    Slide,
    AirAction,
};

class SkillManager final {
private:
    ExecutionManager *manager;
    std::vector<std::shared_ptr<SkillParameter>> Skills;
    int Selected;

    void LoadFromToml(boost::filesystem::path file);

public:
    SkillManager(ExecutionManager *exm);

    void LoadAllSkills();

    void Next();
    void Previous();
    SkillParameter* GetSkillParameter(int relative);
    std::shared_ptr<SkillParameter> GetSkillParameterSafe(int relative);
};

class SkillIndicators final {
private:
    std::vector<SImage*> IndicatorIcons;
    asIScriptFunction *CallbackFunction;
    asIScriptObject *CallbackObject;
    asIScriptContext *CallbackContext;
    asITypeInfo *CallbackObjectType;

public:
    SkillIndicators();
    ~SkillIndicators();

    int GetSkillIndicatorCount();
    SImage* GetSkillIndicatorImage(int index);
    void SetCallback(asIScriptFunction *func);
    int AddSkillIndicator(const std::string &icon);
    void TriggerSkillIndicator(int index);
};

void RegisterSkillTypes(asIScriptEngine *engine);