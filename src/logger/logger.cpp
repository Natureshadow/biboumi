#include <logger/logger.hpp>
#include <config/config.hpp>

Logger::Logger(const int log_level):
  log_level(log_level),
  stream(std::cout.rdbuf()),
  null_buffer{},
  null_stream{&null_buffer}
{
#ifdef SYSTEMD_FOUND
  if (::getenv("JOURNAL_STREAM") != nullptr && this->use_stdout())
    this->use_systemd = true;
#endif
}

Logger::Logger(const int log_level, const std::string& log_file):
  log_level(log_level),
  ofstream(log_file.data(), std::ios_base::app),
  stream(ofstream.rdbuf()),
  null_buffer{},
  null_stream{&null_buffer}
{
}

std::unique_ptr<Logger>& Logger::instance()
{
  static std::unique_ptr<Logger> instance;

  if (!instance)
    {
      const std::string log_file = Config::get("log_file", "");
      const int log_level = Config::get_int("log_level", 0);
      if (log_file.empty())
        instance = std::make_unique<Logger>(log_level);
      else
        instance = std::make_unique<Logger>(log_level, log_file);
    }
  return instance;
}

std::ostream& Logger::get_stream(const int lvl)
{
  if (lvl >= this->log_level)
    return this->stream;
  return this->null_stream;
}
