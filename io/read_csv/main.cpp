/* 
 * @file        main.cpp
 * @brief       Computes simple statistics for trades.
 * @details     Name of the input file (containing trades)
 *              is given as the first argument,
 *              name of the output file is given as
 *              the second argument.
 * @author:     Piotr Gregor < piotrek.gregor at gmail.com >
 * @date        9 Mar 2016
 * copyright    LGPLv2.1
 */

#include <iostream>
#include <string>
#include <sstream>
#include <fstream>
#include <cstdlib>
#include <cstring>

#include <map>


/* uncomment this to log all messages to std::cerr
 * while processing input file */ 
//#define PRINT_TO_CERR

/* this is single threaded program,
 * don't worry about this variable */
unsigned long long int entry;


static void
usage(const char *name)
{
	if (name == NULL)
		return;

    std::cerr << "\nusage:\t " << name << " <input> <output>\n";
    std::cerr << "\nExample:\n" << "	executable input.csv output.csv\n"
                                << "	This will read file input.csv and "
                                << "write result to output.csv.\n\n";
}

/* @brief   Transaction representation.
 * @details Describes each row of the input file. */
class Trade
{
    public:

        friend std::istream&
        operator>>(std::istream& is, Trade& t)
        {
            std::string line, field;
            std::getline(is, line);
            std::istringstream iss(line);
            t.state_ = false;
            if (!getline(iss, field, ','))
                goto fail;
            t.ts_ = std::stoull(field);
            if (!iss.getline(&t.ticker_[0], 4, ','))
                    goto fail;
            if (!getline(iss, field, ','))
                goto fail;
            t.qty_ = std::stoull(field);
            if (!getline(iss, field, ','))
                goto fail;
            t.price_ = std::stoi(field);
         
            t.state_ = true;
            return is;
fail:
#ifdef PRINT_TO_CERR
            std::cerr << "Error reading line [" << entry << "]. Skipping.\n";
#endif
            return is;
        }

        inline bool
        state(void) const
        {
            return state_;
        }

        uint32_t
        ts(void) const
        {
            return ts_;
        }

        uint32_t
        price(void) const
        {
            return price_;
        }

        std::string
        ticker(void) const
        {
            return ticker_;
        }

        uint32_t
        qty(void) const
        {
            return qty_;
        }

    private:

        bool                    state_;  /* true if Trade read successfully,
                                            false - in bad state */
        uint32_t                ts_;
        char                    ticker_[4];
        int                     price_;
        uint32_t                qty_;
};

/* @brief   Summarised statistics for each ticker
 *          found in input file.
 * @details Computes statistics sequentially, i.e.
 *          on each new transaction read from input only
 *          this data + current state of statistics for
 *          that ticker are needed to produce final result. */
class TickerStats
{
    public:
        TickerStats() : ticker_(), last_ts_(0), max_time_gap_(0), volume_(0),
                            max_price_(0), weighted_avg_price_(0)
        {
        }
        TickerStats(std::string ticker, uint32_t ts, uint32_t qty, uint32_t price) :
            ticker_(ticker),
            last_ts_(ts), max_time_gap_(0), volume_(qty), max_price_(price),
            weighted_avg_price_(price)
        {
        }
        friend std::ostream&
        operator<<(std::ostream &os, const TickerStats &ts)
        {
            os << ts.ticker_ << "," << ts.max_time_gap_ << ","
                << ts.volume_ << "," << (uint32_t)ts.weighted_avg_price_ << ","
                << ts.max_price_ << "\n";
            return os;
        }

        std::string                 ticker_;
        uint32_t                    last_ts_, max_time_gap_;
        uint64_t                    volume_;
        uint32_t                    max_price_;
        double                      weighted_avg_price_;   
};

void
debug_print(std::map<std::string, TickerStats> &m)
{
    std::map<std::string, TickerStats>::iterator  it, end;

    std::cerr << "Map size: [" << m.size() << "]\n";
    std::cerr << "Map:\n";
    it = m.begin();
    end = m.end();
    while (it != end)
    {
        TickerStats &ts = it->second;
        std::cerr << "[" << ts.ticker_ << "] MaxTimeGap [" << ts.max_time_gap_
            << "] Volume [" << ts.volume_ << "] WeightedAveragePrice ["
            << ts.weighted_avg_price_ << "] MaxPrice [" << ts.max_price_ << "]\n";
        ++it;
    }
}

/* @brief   Computes simple statistics for trades.
 * @details Error logging is redirected to stderr.    
 * @return  0 on success, negative value on error:
 *          -1: invalid number of arguments,
 *          -2: can't open input file for reading
 *          -3: can't open output file for writing
 */ 
int
main(int argc, char* argv[])
{
    std::string line;
    Trade       t;
    std::map<std::string, TickerStats>            m;
    std::map<std::string, TickerStats>::iterator  it, end;
    uint32_t    ts_gap;

    if (argc != 3)
    {
        usage(argv[0]);
        return -1;
    }

    std::ifstream in(argv[1]);
    if (!in)
    {
        std::cerr << "Error. Can't open file [" 
            << argv[1] << "] for reading.\nPlease make"
            << " sure it exists and you have appropriate"
            << " permisions.\n";
        return -2;
    }

    /* read input file */
    try
    {
        entry = 1;
        while (in >> t)
        {
            if (t.state() == true)
            {
                /* process trade */
                it = m.find(t.ticker());
                if (it != m.end())
                {
                    /* process existing ticker */
                    TickerStats &ts = it->second;
                    /* max gap */
                    ts_gap = t.ts() - it->second.last_ts_;
                    if (ts_gap > ts.max_time_gap_)
                        ts.max_time_gap_ = ts_gap;
                    /* max trade price */
                    if (t.price() > ts.max_price_)
                        ts.max_price_ = t.price();
                    /* weighted average price */
                    double denominator = (double) (ts.volume_ + t.qty());
                    double a = ts.volume_/denominator;
                    double b = t.qty()/denominator;
                    ts.weighted_avg_price_ = a * ts.weighted_avg_price_ + b * t.price();
                    /* update */
                    ts.last_ts_ = t.ts();
                    ts.volume_ += t.qty();
                } else {
                    /* insert new ticker */
                    m[t.ticker()] = TickerStats(t.ticker(), t.ts(), t.qty(), t.price());
                }
            }
            /* next */
            ++entry;
        }
    } catch (std::exception &e)
    {
#ifdef PRINT_TO_CERR
        std::cerr << "Error reading line [" << entry
            << "]. exception [" << e.what() << "]. Skipping.\n";
#endif
    }

    /* write results */
    std::ofstream out(argv[2]);
    if (!out)
    {
        std::cerr << "Error. Can't open file [" 
            << argv[2] << "] for writing." << std::endl;
        return -3;
    }
    it = m.begin();
    end = m.end();
    while (it != end)
    {
        TickerStats &ts = it->second;
        out << ts;
        ++it;
    }

#ifdef DEBUG
    debug_print(m);
#endif

    return 0;
}

