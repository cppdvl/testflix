#include <array>
#include <ctime>
#include <queue>
#include <vector>
#include <cstdlib>
#include <iostream>
#include <cxxopts.hpp>
#include <unordered_map>
#include <nlohmann/json.hpp>
#include <fstream>
#include <iomanip>


namespace TestFlix
{
    using ID = std::uint32_t;
    using MovieID = std::uint32_t;
    using TheaterID = std::uint32_t;
    using MovieIDs = std::vector<MovieID >;
    using TheaterIDs = std::vector<TheaterID >;
    using MovieEvent = std::uint64_t;
    using MovieEvents = std::vector<std::uint64_t >;
    using TheaterAcommodation = std::array<std::uint16_t, 32>;

    //The names
    static std::unordered_map<TheaterID , std::string> idtheaters_theatersname{};
    static std::unordered_map<MovieID , std::string> idmovies_moviesname{};

    //The Locations
    static std::unordered_map<MovieEvent , TheaterAcommodation> event_seats{};

    //The Data
    static MovieIDs idmovies{};
    static TheaterIDs idtheaters{};
    static MovieEvents idmovies_idtheaters{};

    enum class Entity
    {
        MOVIE,
        THEATER
    };

    static MovieIDs SelectMoviesByTheater(TheaterID theater){
        auto movies = MovieIDs {};
        const std::uint32_t theatermask = 0xffffffff;
        for(auto& id_id : idmovies_idtheaters)
        {
            TheaterID theater_id = id_id & theatermask;
            if (theater_id == theater) movies.push_back(id_id >> 32);
        }
        return movies;
    }
    static TheaterIDs SelectTheatersByMovie(MovieID movie){
        auto theaters = TheaterIDs {};
        const std::uint64_t moviemask = 0xffffffff00000000;
        for(auto& id_id : idmovies_idtheaters)
        {
            MovieID movie_id = (id_id & moviemask) >> 32;
            if (movie_id == movie) theaters.push_back(id_id & 0xffffffff);
        }
        return theaters;
    }

    std::string& GetStringFromID(Entity entity, uint32_t id)
    {
        return  entity == Entity::MOVIE ? idmovies_moviesname[id] : idtheaters_theatersname[id];
    }

}

namespace TestFlix::Session{

    void Populate();
    static void Reset()
    {
        idmovies.clear();
        idtheaters.clear();
        event_seats.clear();
        idmovies_idtheaters.clear();
        idmovies_moviesname.clear();
        idtheaters_theatersname.clear();


        Populate();
    }
    static void Populate()
    {
        std::ifstream i("data.json");
        nlohmann::json j;
        i >> j;
        i.close();

        auto moviescount = j["movies"].size();

        auto theaterscount = j["theaters"].size();

        auto theaters = j["theaters"];
        for(auto& theater : theaters)
        {
            idtheaters_theatersname.insert(std::make_pair(theater["id"], theater["name"]));
            idtheaters.push_back(theater["id"]);
        }

        auto movies = j["movies"];
        for (auto& movie : movies)
        {
            idmovies_moviesname.insert(std::make_pair(movie["id"], movie["name"]));
            idmovies.push_back(movie["id"]);
        }

        //Randomize the world, generate theaters and featured movies pairs.
        srand((unsigned) time(0));
        for (auto& id_name : idtheaters_theatersname)
        {

            auto bag_of_movies = std::vector<uint32_t >(idmovies.begin(), idmovies.end());
            auto bag_size = bag_of_movies.size();
            for (auto movies_featured = (rand() % moviescount) + 1; movies_featured; --movies_featured, --bag_size)
            {
                auto pick_a_movie_index = rand() % bag_size;

                uint64_t idmovie_idtheater = bag_of_movies[pick_a_movie_index];
                idmovie_idtheater <<= 32; //Encode idmovie
                idmovie_idtheater += id_name.first; //Encode idtheater
                idmovies_idtheaters.push_back(idmovie_idtheater);

                bag_of_movies.erase(bag_of_movies.begin() + pick_a_movie_index);
            }
        }

        //Start bookables
        event_seats.clear();
        for(auto& idmovie_idtheater : idmovies_idtheaters){
            event_seats[idmovie_idtheater] = TheaterAcommodation {};
        }

    }

}

namespace TestFlix::Public {

    std::vector <std::pair<MovieID , std::string>> GetMovies()
    {
        std::vector <std::pair<std::uint32_t , std::string>> movies{};
        for (auto& k_v : TestFlix::idmovies_moviesname){
            movies.push_back(std::make_pair(k_v.first, k_v.second));
        }
        return movies;
    }
    std::vector <std::pair<TheaterID , std::string>> GetTheaters(MovieID movie)
    {
        std::vector <std::pair<std::uint32_t , std::string>> theaters{};
        auto theater_ids = SelectTheatersByMovie(movie);
        for (auto& theater_id : theater_ids){
            theaters.push_back(std::make_pair(theater_id, idtheaters_theatersname[theater_id]));
        }
        return theaters;
    }

}


class Application{

    TestFlix::MovieID mMovieSelected{0};
    TestFlix::MovieEvent mEventSelected{0};

    void Reset(){

        std::cout << "Reset" << std::endl;
        TestFlix::Session::Reset();

    }

    void PrintList(std::vector<std::pair<TestFlix::ID, std::string>>&list) const
    {

        for (const auto& tid_tname : list)
        {
            std::cout << "\t[ " << tid_tname.first << " ] " << tid_tname.second << std::endl;
        }

    }

    void PrintAccomodations()
    {
        TestFlix::MovieEvent event = mEventSelected;
        auto data = TestFlix::event_seats[event];

        std::cout << std::endl;
        std::cout << "   ";

        for(auto index = 0; index < 16; ++index)
        {
            std::cout << " " << std::setw(2) << index << " ";
            if (index == 15) std::cout << std::endl;
        }

        auto rownumber = 0U;
        for (auto row : data)
        {
            std::cout << std::setw(2) << rownumber << " ";
            for(auto index = 0; index < 16; ++index)
            {
                std::cout << (row & 0x1 ? "[  ]" : "[xx]");
                row >>= 1;
                if (index == 15) std::cout << std::endl;
            }
            rownumber++;
        }
    }

    enum class ParentSeatPosition{
        NONE, RIGHT, LEFT, UP, DOWN
    };
    void BookSeat(std::vector<std::string>& bookedstrings, TestFlix::MovieEvent event, unsigned int row, unsigned int col, unsigned int& ticketsToBook, ParentSeatPosition parentChairUbication)
    {
        auto& rowaccomodations = TestFlix::event_seats[event][row];
        if ((rowaccomodations >> col) & 0x01)
        {
            //Seat No Available
            return;
        }
        else
        {
            //Ok Book Seat
            rowaccomodations |= (1 << col);
            ticketsToBook--;

            //Track
            std::stringstream ss;
            ss << "Row: " << row << ", Col: " << col << std::endl;
            bookedstrings.push_back(ss.str());

            //Still needing tickets? Ok Try To Book Left.
            if (ticketsToBook && col && parentChairUbication != ParentSeatPosition::LEFT)
                BookSeat(bookedstrings, event, row, col - 1, ticketsToBook, ParentSeatPosition::RIGHT);
            //Still needing tickets? Ok Try To Book right.
            if (ticketsToBook && col < 15 && parentChairUbication != ParentSeatPosition::RIGHT)
                BookSeat(bookedstrings, event, row, col + 1, ticketsToBook, ParentSeatPosition::LEFT);
            //Still needing tickets? Ok Try To Book screen closer row / up.
            if (ticketsToBook && row && parentChairUbication != ParentSeatPosition::UP)
                BookSeat(bookedstrings, event, row - 1, col, ticketsToBook, ParentSeatPosition::DOWN);
            //Still needing tickets? Ok Try To Book screen father row.
            if (ticketsToBook && row < 31 && parentChairUbication != ParentSeatPosition::DOWN)
                BookSeat(bookedstrings, event, row + 1, col, ticketsToBook, ParentSeatPosition::UP);

            //Still needing tickets?... mmm we don't have that many available seats.
            if (ticketsToBook){
                //Unbook
                rowaccomodations &= ~ (1 <<col);
                ticketsToBook++;
                bookedstrings.erase(bookedstrings.end() - 1);
            }
            return;

        }

    }
public:

    void ListMovies(){

        std::cout << "Movies being featured: " << std::endl;
        auto movies = TestFlix::Public::GetMovies();
        PrintList(movies);
    }

    void SelectMovie(const TestFlix::MovieID& movieid){
        mMovieSelected = movieid;
    }
    void SelectTheater(const TestFlix::TheaterID& theaterId)
    {
        if (mMovieSelected == 0)
        {
            std::cout << "Movie has not being selected yet....";
            return;
        }

        auto theaters = TestFlix::Public::GetTheaters(mMovieSelected);
        if (theaters.empty())
        {
            std::cout << "No theater is presenting that movie" << std::endl;
            return;
        }
        mEventSelected = mMovieSelected;
        mEventSelected <<= 32;
        mEventSelected += theaterId;

    }
    void ListTheaters() const{

        if (mMovieSelected == 0)
        {
            std::cout << "Movie has not being selected yet....";
            return;
        }

        auto theaters = TestFlix::Public::GetTheaters(mMovieSelected);
        if (theaters.empty())
        {
            std::cout << "No theater is presenting that movie" << std::endl;
        }

        std::cout <<
                  TestFlix::GetStringFromID(TestFlix::Entity::MOVIE, mMovieSelected) <<
                  " featured at the following location" <<
                  ((theaters.size() > 1) ? "s: " : ": ") <<
                  std::endl << std::endl;

        Application::PrintList(theaters);

    }

    void BookSeats(TestFlix::MovieEvent movieEvent,
                   std::uint32_t row,
                   std::uint32_t col,
                   std::uint32_t qty)
    {
        std::cout << "Trying to get tickets for " << TestFlix::GetStringFromID(TestFlix::Entity::MOVIE, movieEvent>>32) << " at " << TestFlix::GetStringFromID(TestFlix::Entity::THEATER, movieEvent & 0xffffffff) << std::endl;
        std::cout << "Booking location row: " << row << " col:" << col << " qty: " << qty << std::endl;
        std::vector<std::string> ticketbookingstrings{};
        if (!qty) return;
        BookSeat(ticketbookingstrings, movieEvent, row, col, qty, ParentSeatPosition::NONE);
        if (!qty)
        {
            std::cout << "Tickets Booked:\n" << std::endl;
            for (auto& ticketbookingstring: ticketbookingstrings){
                std::cout << ticketbookingstring << std::endl;
            }
        }
    }


    Application(cxxopts::ParseResult& parseResult)
    {
        Reset();
        if (parseResult["M"].as<bool>()){
            ListMovies();
        }
        auto selectedMovieID = parseResult["m"].as<std::uint32_t>();
        if (selectedMovieID)
        {
            SelectMovie(selectedMovieID);
        }
        if (parseResult["T"].as<bool>()){
            ListTheaters();
        }
        auto selectedTheaterID = parseResult["t"].as<std::uint32_t>();
        if (selectedTheaterID)
        {
            SelectTheater(selectedTheaterID);
            PrintAccomodations();
        }

        auto rcq = std::make_tuple(
                parseResult["r"].as<std::uint32_t>(),
                parseResult["c"].as<std::uint32_t>(),
                parseResult["q"].as<std::uint32_t>()
                );
        auto& [r,c,q] = rcq;

        if (r >= 0 && r < 32 && c >= 0 && c != 16){
            if (!mEventSelected)
            {
                std::cout << "Trying to get tickets but not movie and theater had been selected.... " << std::endl;
                return;
            }
            BookSeats(mEventSelected, r, c, q);
            PrintAccomodations();
        }

    }







};

int main(int argc, char** argv) {

    //Options:
    //-S port
    //-r, --reset => If this option is invoked it will be first than any other.
    //-M => Display a List of All MovieIDs.
    //-m id, --select_movie=id => selects a movie.
    //-T => Show a List of theaters for the movie selected with -m.
    //-t id, --select_theater=id => selects a theater.
    //-b loc,n, --book=locid => book loc id.
    //LOC ID : [4][4][4] = Upper Nibble Row, High Nible Column, Number of Tickets

    auto options = cxxopts::Options("TestFlix", "A C++ Test Demo");
    options.add_options()
            ("h, help", "Print this...")
            ("m, select_movie", "Integer to select an ID of a movie",
                    cxxopts::value<std::uint32_t>()->default_value("0"))//default 0
            ("t, select_theater", "Interger to ID of a theater",
                    cxxopts::value<std::uint32_t>()->default_value("0"))
            ("M", "Show a list of available movies and movies id", cxxopts::value<bool>()->default_value("false"))
            ("T", "Show a list available theaters and theaters id", cxxopts::value<bool>()->default_value("false"))
            ("r, row", "Select a row where is the seat to book",
                    cxxopts::value<std::uint32_t>()->default_value("32"))
            ("c, col", "Select a col where is the seat to book",
                    cxxopts::value<std::uint32_t>()->default_value("16"))
            ("q, qty", "Number of tickets to book",
                    cxxopts::value<std::uint32_t>()->default_value("1"))

            /*("s, simulate", "Simulate n-concurrent booking requesters",
                    cxxopts::value<std::uint32_t>()->default_value("0"))
            ("a, assertions", "Run tests....",
             cxxopts::value<bool>()->default_value("false"))*/;

    auto parse = options.parse(argc, argv);
    if (parse["h"].as<bool>()){
        std::cout << options.help() << std::endl;
        return 0;
    }

    Application app(parse);




    std::cout << "Hello, World!" << std::endl;
    return 0;
}
