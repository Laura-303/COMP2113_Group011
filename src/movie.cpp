#include "Movie.h"
#include <sstream>
#include <vector>

static std::vector<std::string> split(const std::string& s, char delim) {
    std::vector<std::string> toks;
    std::string t;
    std::istringstream iss(s);
    while (std::getline(iss, t, delim)) toks.push_back(t);
    return toks;
}

static bool parseInt(const std::string& s, int& out) {
    if (s.empty()) return false;
    std::istringstream iss(s);
    int v;
    if (!(iss >> v)) return false;
    char extra;
    if (iss >> extra) return false;
    out = v;
    return true;
}

Movie::Movie() : id(""), title(""), genre(""), duration(0), rating("") {}

Movie::Movie(const std::string& id,
             const std::string& title,
             const std::string& genre,
             int duration,
             const std::string& rating)
    : id(id), title(title), genre(genre), duration(duration), rating(rating) {}

const std::string& Movie::getId() const
{
    return id;
}
const std::string& Movie::getTitle()  const { return title; }
const std::string& Movie::getGenre()  const { return genre; }
int                Movie::getDuration() const { return duration; }
const std::string& Movie::getRating() const { return rating; }

void Movie::setId(const std::string& v)     { id = v; }
void Movie::setTitle(const std::string& v)  { title = v; }
void Movie::setGenre(const std::string& v)  { genre = v; }
void Movie::setDuration(int v)              { duration = v; }
void Movie::setRating(const std::string& v) { rating = v; }

std::string Movie::toFileLine() const {
    std::ostringstream oss;
    oss << id << "|" << title << "|" << genre << "|"
        << duration << "|" << rating;
    return oss.str();
}

bool Movie::isValidLine(const std::string& line) {
    std::vector<std::string> t = split(line, '|');
    if (t.size() != 5u) return false;
    if (t[0].empty() || t[1].empty()) return false;
    int d = 0;
    if (!parseInt(t[3], d) || d <= 0) return false;
    return true;
}

Movie Movie::fromFileLine(const std::string& line) {
    std::vector<std::string> t = split(line, '|');
    Movie empty;
    if (t.size() != 5u) return empty;
    int d = 0;
    if (!parseInt(t[3], d) || d <= 0) return empty;
    return Movie(t[0], t[1], t[2], d, t[4]);
}