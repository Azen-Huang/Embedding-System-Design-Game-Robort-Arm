#include <iostream>
#include <vector>
#include <cstdlib>
#include <ctime>
#include <Windows.h>
#include <Windows.Devices.Bluetooth.h>
#include <Windows.Devices.Enumeration.h>
using namespace std;
using namespace Windows::Devices::Bluetooth;
using namespace Windows::Devices::Enumeration;
enum class Player { X, O };

struct Move
{
    int x, y;
};

struct GameState
{
    std::vector<std::vector<Player>> board;
    Player turn;

    GameState()
        : board(3, std::vector<Player>(3, Player::O))
        , turn(Player::X){}

    bool is_game_over() const
    {
        for (int i = 0; i < 3; i++)
        {
            if (board[i][0] != Player::O && board[i][0] == board[i][1] && board[i][1] == board[i][2])
                return true;

            if (board[0][i] != Player::O && board[0][i] == board[1][i] && board[1][i] == board[2][i])
                return true;
        }

        if (board[0][0] != Player::O && board[0][0] == board[1][1] && board[1][1] == board[2][2])
            return true;

        if (board[0][2] != Player::O && board[0][2] == board[1][1] && board[1][1] == board[2][0])
            return true;

        for (int i = 0; i < 3; i++)
        {
            for (int j = 0; j < 3; j++)
            {
                if (board[i][j] == Player::O)
                    return false;
            }
        }

        return true;
    }

    std::vector<Move> get_valid_moves() const
    {
        std::vector<Move> moves;

        for (int i = 0; i < 3; i++)
        {
            for (int j = 0; j < 3; j++)
            {
                if (board[i][j] == Player::O)
                {
                    moves.push_back({i, j});
                }
            }
        }

        return moves;
    }

    void make_move(const Move& move)
    {
        board[move.x][move.y] = turn;
        turn = (turn == Player::X) ? Player::O : Player::X;
    }
};
struct Node{
    GameState state;
    std::vector<Node*> children;
    Node* parent;
    int wins;
    int visits;
    Node(const GameState& state, Node* parent = nullptr)
    : state(state), parent(parent), wins(0), visits(0){}

    ~Node()
    {
        for (Node* child : children)
        {
            delete child;
        }
    }

    void add_child(Node* child)
    {
        children.push_back(child);
    }

    int get_uct() const
    {
        return wins / visits + std::sqrt(2 * std::log(parent->visits) / visits);
    }
};

Node* create_tree(Node* root, int itermax){
    for (int i = 0; i < itermax; i++){
        Node* node = root;
        while (!node->state.is_game_over() && !node->children.empty())
        {
            int best_uct = -1;
            Node* best_child = nullptr;

            for (Node* child : node->children)
            {
                int uct = child->get_uct();

                if (uct > best_uct)
                {
                    best_uct = uct;
                    best_child = child;
                }
            }

            node = best_child;
        }

        GameState state = node->state;

        while (!state.is_game_over())
        {
            std::vector<Move> moves = state.get_valid_moves();
            state.make_move(moves[rand() % moves.size()]);
        }

        while (node != nullptr)
        {
            node->visits++;

            if (node->state.turn == state.turn)
            {
                node->wins++;
            }

            node = node->parent;
        }
    }

    return root;
}

Move get_best_move(Node* root){
    int best_uct = -1;
    Move best_move;
    for (Node* child : root->children)
    {
        int uct = child->get_uct();

        if (uct > best_uct)
        {
            best_uct = uct;
            best_move = {child->state.board[0][0], child->state.board[1][1]};
        }
    }
    return best_move;
}


void MCTS(vector<int>& board_1D){
    Node* root = new Node(GameState());

    for (int i = 0; i < 3; i++){
        for (int j = 0; j < 3; j++){
            GameState state = root->state;
            state.make_move({i, j});
            root->add_child(new Node(state, root));
        }
    }
    root = create_tree(root, 1000);
    for(int i = 0; i < 3; ++i){
        root = root->children[board_1D[0]];
    }
    
    return get_best_move(root).x * 3 + get_best_move(root).y;
}

int main(){
    auto devices = DeviceInformation::FindAllAsync(RfcommDeviceService::GetDeviceSelector(RfcommServiceId::SerialPort));
    auto device = devices.GetResults().First();

    while(true){
        auto rfcommService = RfcommDeviceService::FromIdAsync(device->Id);
        auto socket = ref new StreamSocket();
        socket->ConnectAsync(rfcommService->Service->ConnectionHostName, rfcommService->Service->ConnectionServiceName);
        
        auto inputStream = socket->InputStream;

        DataReader^ reader = ref new DataReader(inputStream);

        int arrayLength = reader->ReadInt32();

        vector<int> board(arrayLength);

        for (int i = 0; i < arrayLength; i++) {
            board[i] = reader->ReadInt32();
        }

        int pos = MCTS(board);

        auto outputStream = socket->OutputStream;

        DataWriter^ writer = ref new DataWriter(outputStream);

        writer->WriteInt32(pos);

        writer->StoreAsync();
    }

}