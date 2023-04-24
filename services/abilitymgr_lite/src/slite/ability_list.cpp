/*
 * Copyright (c) 2020 Huawei Device Co., Ltd.
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *     http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

#include <cstring>
#include "ability_record.h"
#include "ability_list.h"


namespace OHOS {
namespace AbilitySlite {
namespace {
constexpr uint16_t ABILITY_LIST_CAPACITY = 10240;
}

void AbilityList::Add(AbilityRecord *abilityRecord)
{
    if (abilityRecord == nullptr || abilityList_.Size() >= ABILITY_LIST_CAPACITY) {
        return;
    }

    if (Get(abilityRecord->token) == nullptr) {
        abilityList_.PushBack(abilityRecord);
    }
}

AbilityRecord *AbilityList::Get(uint16_t token) const
{
    for (auto node = abilityList_.Begin(); node != abilityList_.End(); node = node->next_) {
        AbilityRecord *record = node->value_;
        if (record == nullptr) {
            continue;
        }
        if (record->token == token) {
            return record;
        }
    }

    return nullptr;
}

AbilityRecord *AbilityList::Get(const char *bundleName) const
{
    if (bundleName == nullptr) {
        return nullptr;
    }

    for (auto node = abilityList_.Begin(); node != abilityList_.End(); node = node->next_) {
        AbilityRecord *record = node->value_;
        if (record == nullptr || record->appName == nullptr) {
            continue;
        }
        if (strcmp(bundleName, record->appName) == 0) {
            return record;
        }
    }

    return nullptr;
}

AbilityRecord *AbilityList::GetByTaskId(uint32_t taskId) const
{
    for (auto node = abilityList_.Begin(); node != abilityList_.End(); node = node->next_) {
        AbilityRecord *record = node->value_;
        if (record == nullptr) {
            continue;
        }
        if (record->taskId == taskId) {
            return record;
        }
    }

    return nullptr;
}

void AbilityList::Erase(uint16_t token)
{
    for (auto node = abilityList_.Begin(); node != abilityList_.End(); node = node->next_) {
        AbilityRecord *record = node->value_;
        if (record == nullptr) {
            continue;
        }
        if (record->token == token) {
            abilityList_.Remove(node);
            return;
        }
    }
}
} // namespace AbilitySlite
} // namespace OHOS