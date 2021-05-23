#ifndef PARSERTESTS_H
#define PARSERTESTS_H

#include "../../engine.h"
#include "../../parser.h"

std::vector<Engine::SubtitleItem> getSubtitles(ParserInterface &parser,
                                               QString content);
void assertSubtitles(std::vector<Engine::SubtitleItem> subtitles);

#endif // PARSERTESTS_H
