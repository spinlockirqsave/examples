/* 
 * File:   logger.h
 * Author: piter cf16.eu
 *
 * Created on September 26, 2013, 7:01 PM
 */

#ifndef LOGGER_H
#define	LOGGER_H



    namespace borders {
    namespace common {
    namespace log {
            class Logger {

  public:
    Logger() : _has_logged_something(false) { };

    template <typename T>
    friend Logger& operator <<(Logger& logger, T const & value) {
      logger._has_logged_something = true;
      std::cerr << value;
      return logger;
    };

  private:
    bool _has_logged_something;

};

    }
    }
    }




#endif	/* LOGGER_H */

