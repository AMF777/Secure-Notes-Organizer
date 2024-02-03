#ifndef ParseJsonMesssge_H
#define ParseJsonMesssge_H

#include <string>

#include "ServerWithDC.h"

#include <json.hpp>

using json = nlohmann::json;

json processJsonMessage(const json& message);

static json checkAction(const json& message);

static void processSignupMessage(const json& message, json& responseMessage);
static void processLoginMessage(const json& message, json& responseMessage);

static void processCreateNoteMessage(const json& message, json& responseMessage);
static void processUpdateNoteTitleMessage(const json& message, json& responseMessage);
static void processDeleteNoteMessage(const json& message, json& responseMessage);

static void processListNotesMessage(const json& message, json& responseMessage);
static void processSearchByTitleMessage(const json& message, json& responseMessage);

static void processCreateComponentMessage(const json& message, json& responseMessage);
static void processUpdateComponentMessage(const json& message, json& responseMessage);
static void processDeleteComponentMessage(const json& message, json& responseMessage);
static void processListComponentsMessage(const json& message, json& responseMessage);

static void processAddTagMessage(const json& message, json& responseMessage);
static void processUpdateTagMessage(const json& message, json& responseMessage);
static void processDeleteTagMessage(const json& message, json& responseMessage);
static void processFilterByTagNameMessage(const json& message, json& responseMessage);

#endif // ParseJsonMesssge_H
