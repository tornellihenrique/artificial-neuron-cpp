#include <random>
#include <map>

namespace Tornelli
{
    typedef std::pair<int, int> Pair;

    enum Operation
    {
        OR = 0,
        AND = 1,
        NOR = 2,
        NAND = 3,
        XOR = 4
    };

    static Pair examples[4] = {
        std::make_pair(0, 0),
        std::make_pair(0, 1),
        std::make_pair(1, 0),
        std::make_pair(1, 1)};

    static int expectedResultsMatrix[5][2][2] = {
        {
            // OR
            {
                0, // OR - 0 - 0 = 0
                1, // OR - 0 - 1 = 1
            },
            {
                1, // OR - 1 - 0 = 1
                1, // OR - 1 - 1 = 1
            },
        },
        {
            // AND
            {
                0, // AND - 0 - 0 = 0
                0, // AND - 0 - 1 = 0
            },
            {
                0, // AND - 1 - 0 = 0
                1, // AND - 1 - 1 = 1
            },
        },
        {
            // NOR
            {
                1, // NOR - 0 - 0 = 1
                0, // NOR - 0 - 1 = 0
            },
            {
                0, // NOR - 1 - 0 = 0
                0, // NOR - 1 - 1 = 0
            },
        },
        {
            // NAND
            {
                1, // NAND - 0 - 0 = 1
                1, // NAND - 0 - 1 = 1
            },
            {
                1, // NAND - 1 - 0 = 1
                0, // NAND - 1 - 1 = 0
            },
        },
        {
            // XOR
            {
                0, // XOR - 0 - 0 = 0
                1, // XOR - 0 - 1 = 1
            },
            {
                1, // XOR - 1 - 0 = 1
                0, // XOR - 1 - 1 = 0
            },
        }};

    static std::string opToString(Operation op)
    {
        switch (op)
        {
        case Operation::OR:
            return "OR";
        case Operation::AND:
            return "AND";
        case Operation::NOR:
            return "NOR";
        case Operation::NAND:
            return "NAND";
        case Operation::XOR:
            return "XOR";
        default:
            return "OR";
        }
    }

    class Neuron
    {

    private:
        const int LIMIT = 1000;
        const int BIAS = -1;
        const float N = 0.1f;

        Operation op;
        double w[3];

        int transfer(double net)
        {
            return net > 0.f ? 1 : 0;
        }

        void fix(const Pair &example, int result)
        {
            w[0] = w[0] + (N * (expectedResultsMatrix[op][example.first][example.second] - result) * (BIAS));
            w[1] = w[1] + (N * (expectedResultsMatrix[op][example.first][example.second] - result) * (example.first));
            w[2] = w[2] + (N * (expectedResultsMatrix[op][example.first][example.second] - result) * (example.second));
        }

    public:
        Neuron(Operation _op) : op(_op)
        {
            // Set random weights values between -1 and 1
            std::uniform_real_distribution<double> unif(-1, 1);
            std::default_random_engine re;
            for (int i = 0; i < 3; i++)
                w[i] = unif(re);
        }

        int execute(int x1, int x2)
        {
            return transfer((BIAS * w[0]) + (x1 * w[1]) + (x2 * w[2]));
        }

        void train()
        {

            bool done;
            int i = 0;

            do
            {
                done = true;

                for (auto example : examples)
                {
                    const int result = execute(example.first, example.second);

                    if (result != expectedResultsMatrix[op][example.first][example.second])
                    {
                        done = false;
                        fix(example, result);
                    }
                }

                i++;
            } while (!done && i < LIMIT);
        }
    };
}