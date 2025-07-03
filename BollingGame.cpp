#include <iostream>
#include <vector>
#include <limits>
#include <stdexcept>
#include <optional>
#include <memory>

// Constants
constexpr int MAX_FRAME = 10;
constexpr int MAX_PINS = 10;

// Roll Class (Represents a single roll)
class Roll {
public:
    int pins;

    explicit Roll(int pins) : pins(pins) {
        if (pins < 0 || pins > MAX_PINS) {
            throw std::invalid_argument("Invalid number of pins.");
        }
    }

    bool isStrike() const {
        return pins == MAX_PINS;
    }

    bool isSpare(const Roll& nextRoll) const {
        return (pins + nextRoll.pins == MAX_PINS);
    }
};

// Frame Class (Represents a frame consisting of up to two rolls and their score)
class Frame {
private:
    Roll firstRoll;
    Roll secondRoll;
    std::unique_ptr<Roll> thirdRoll;  // Using unique_ptr for third roll

public:
    Frame(int firstPins, int secondPins)
        : firstRoll(firstPins), secondRoll(secondPins) {}

    void setThirdRoll(int pins) {
        thirdRoll = std::make_unique<Roll>(pins);  // Use make_unique to allocate memory
    }

    int score() const {
        int totalScore = firstRoll.pins + secondRoll.pins;
        if (thirdRoll) {
            totalScore += thirdRoll->pins;
        }
        return totalScore;
    }

    bool isStrike() const {
        return firstRoll.isStrike();
    }

    bool isSpare() const {
        return firstRoll.isSpare(secondRoll);
    }

    const Roll& getFirstRoll() const {
        return firstRoll;
    }

    const Roll& getSecondRoll() const {
        return secondRoll;
    }

    bool hasThirdRoll() const {
        return thirdRoll != nullptr;
    }
};

// Bowling Game Class (Manages the entire game)
class BowlingGame {
private:
    std::vector<Frame> frames;

    bool isValidRoll(int pins) const {
        return pins >= 0 && pins <= MAX_PINS;
    }

public:
    void addFrame(int firstPins, int secondPins, int thirdPins = -1) {
        if (!isValidRoll(firstPins) || !isValidRoll(secondPins)) {
            throw std::invalid_argument("Invalid roll count.");
        }

        Frame frame(firstPins, secondPins);
        if (thirdPins != -1 && isValidRoll(thirdPins)) {
            frame.setThirdRoll(thirdPins);
        }

        frames.push_back(std::move(frame));
    }

    int calculateScore() const {
        int totalScore = 0;
        for (int i = 0; i < MAX_FRAME; ++i) {
            const Frame& frame = frames[i];
            totalScore += frame.score();

            // Add bonus for strikes and spares
            if (frame.isStrike() && i < MAX_FRAME - 1) {
                const Frame& nextFrame = frames[i + 1];
                totalScore += nextFrame.getFirstRoll().pins;
                if (nextFrame.isStrike() && i + 2 < MAX_FRAME) {
                    const Frame& nextNextFrame = frames[i + 2];
                    totalScore += nextNextFrame.getFirstRoll().pins;
                } else {
                    totalScore += nextFrame.getSecondRoll().pins;
                }
            } 
            else if (frame.isSpare() && i < MAX_FRAME - 1) {
                totalScore += frames[i + 1].getFirstRoll().pins;
            }
        }

        return totalScore;
    }

    bool isGameComplete() const {
        return frames.size() == MAX_FRAME;
    }
};

// Input Validator Class
class InputValidator {
public:
    static bool readValidInt(int& value) {
        std::cin >> value;
        if (std::cin.fail() || value < 0 || value > MAX_PINS) {
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            return false;
        }
        return true;
    }
};

// Main program
int main() {
    BowlingGame game;
    int input;

    std::cout << "Enter bowling scores for 10 frames.\n";
    std::cout << "Each roll must be a number between 0 and 10.\n";

    // Loop for 10 frames
    for (int frame = 1; frame <= MAX_FRAME; ++frame) {
        int firstRoll, secondRoll, thirdRoll = -1;

        // Frame 10 requires a third roll if a strike or spare is hit
        if (frame == MAX_FRAME) {
            std::cout << "Frame 10, Trial 1: ";
            while (!InputValidator::readValidInt(firstRoll) || firstRoll > MAX_PINS) {
                std::cout << "Invalid roll. Enter a number between 0 and 10.\n";
            }

            std::cout << "Frame 10, Trial 2: ";
            while (!InputValidator::readValidInt(secondRoll) || secondRoll > MAX_PINS || firstRoll + secondRoll > MAX_PINS) {
                std::cout << "Invalid second roll. The total for the frame cannot exceed 10.\n";
            }

            // If first roll or second roll is a strike or spare, allow third roll
            if (firstRoll == MAX_PINS || firstRoll + secondRoll == MAX_PINS) {
                std::cout << "Frame 10, Trial 3: ";
                while (!InputValidator::readValidInt(thirdRoll) || thirdRoll > MAX_PINS) {
                    std::cout << "Invalid third roll.\n";
                }
            }

            game.addFrame(firstRoll, secondRoll, thirdRoll);  // Add frame 10
        } else {
            std::cout << "Frame " << frame << ", Trial 1: ";
            while (!InputValidator::readValidInt(firstRoll) || firstRoll > MAX_PINS) {
                std::cout << "Invalid roll. Enter a number between 0 and 10.\n";
            }

            std::cout << "Frame " << frame << ", Trial 2: ";
            while (!InputValidator::readValidInt(secondRoll) || secondRoll > MAX_PINS || firstRoll + secondRoll > MAX_PINS) {
                std::cout << "Invalid second roll. The total for the frame cannot exceed 10.\n";
            }

            game.addFrame(firstRoll, secondRoll);  // Add regular frame
        }
    }

    // Calculate and display total score
    int totalScore = game.calculateScore();
    std::cout << "\nTotal Score: " << totalScore << std::endl;

    return 0;
}
