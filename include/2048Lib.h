#ifndef _2048_Lib_H_
#define _2048_Lib_H_

#include <iostream>
#include <cstdlib> // Thư viện để sinh số ngẫu nhiên
#include <ctime> // Thư viện để lấy seed thời gian thực
#include <fstream> // Thư viện để tương tác với file: đọc, ghi, lưu kết quả, ...
#include <sstream> // Thư viện để chuyển đổi dữ liệu string từ file thành int
#include <cstring> // Thư viện để xử lý các mảng ký tự
#include <utility> // Thư viện để sử dụng swap
#include <filesystem> // Thư viện để tạo thư mục lưu game
#include <SFML/Graphics.hpp> // Thư viện tạo giao diện đồ họa
#include <SFML/Window.hpp> // Thư viện quản lý cửa sổ và các sự kiện của cửa sổ (đóng cửa sổ, nhập liệu từ bàn phím, chuột)
#include <SFML/System.hpp> // Thư viện hỗ trợ các thao tác về thời gian

#define MAXLEN 100

#include "Node.h"
#include "ToaDo.h"
#include "PlayerInfo.h"
#include "Game.h"
#include "Data.h"
#include "NewGame.h"
#include "Controls.h"
#include "GameLogic.h"
#include "Graphics.h"
#include "UndoRedo.h"
#include "FreeMemory.h"



// /* ================= Controls.CPP ================= */



/**
 * Hàm xử lý sự kiện bàn phím trong cửa sổ game và trả về phím được nhấn
 * @param window: Đối tượng cửa sổ SFML để nhận sự kiện
 * @param bang: Con trỏ cấp 2 đại diện cho bảng trò chơi
 * @param size: Kích thước của bảng trò chơi
 * @param currentNode: Con trỏ đến node hiện tại trong danh sách liên kết lưu trạng thái undo/redo
 * @param username: Tên người chơi, được sử dụng để quản lý dữ liệu trò chơi
 * @return Mã phím SFML được nhấn, hoặc thoát chương trình nếu cửa sổ bị đóng
 */
sf::Keyboard::Key control(sf::RenderWindow& window, int** bang, const int& size, Node*& currentNode, char*& username);



// /* ================= Data.CPP ================= */



/**
 * Hàm kiểm tra và tạo file cơ sở dữ liệu nhị phân trong thư mục "data"
 * @param fileName: Tên file cần tạo (không bao gồm phần mở rộng)
 * 
 * Nếu thư mục "data" chưa tồn tại, hàm sẽ tự động tạo. Nếu file chưa tồn tại, 
 * hàm sẽ tạo một file nhị phân rỗng với tên tương ứng trong thư mục "data".
 */
void database(const char* fileName);

/**
 * Hàm xử lý nhập tên người chơi và kiểm tra dữ liệu tồn tại
 * @param window: Đối tượng cửa sổ SFML để hiển thị giao diện nhập tên
 * @param font: Phông chữ sử dụng để hiển thị thông báo trên màn hình
 * @param username: Mảng ký tự chứa tên người chơi sau khi nhập
 * 
 * Hàm cho phép người chơi nhập tên mới hoặc tiếp tục với tên đã có.
 * Nếu chọn bắt đầu trò chơi mới, tên sẽ được kiểm tra tránh trùng lặp.
 * Nếu chọn tiếp tục trò chơi, tên phải tồn tại trong danh sách lưu.
 */
void playerName(sf::RenderWindow& window, const sf::Font& font, char* username);

/**
 * Hàm đọc dữ liệu trò chơi đã lưu từ file và khôi phục trạng thái bảng chơi
 * @param currentNode: Con trỏ tham chiếu đến node đầu tiên trong danh sách liên kết (undo/redo)
 * @param size: Biến tham chiếu lưu kích thước bảng chơi được đọc từ file
 * @param username: Tên người chơi, được sử dụng để tìm file lưu trong thư mục "Saves"
 * @param character: Biến tham chiếu lưu thông tin nhân vật được đọc từ file
 * @return Con trỏ cấp 2 đại diện cho bảng trò chơi đã lưu. Trả về nullptr nếu không tìm thấy file lưu.
 * 
 * Hàm mở file nhị phân dựa trên tên người chơi, đọc kích thước bảng, nhân vật,
 * và khôi phục danh sách liên kết lưu trạng thái undo/redo.
 */
int** loadSave(Node *&currentNode, int& size, const char* username, int& character);

/**
 * Hàm lưu trạng thái trò chơi vào file nhị phân
 * @param head: Con trỏ đến node đầu tiên trong danh sách liên kết lưu trạng thái undo/redo
 * @param size: Kích thước bảng trò chơi
 * @param username: Tên người chơi, được sử dụng để tạo file lưu tương ứng trong thư mục "Saves"
 * @param character: Thông tin nhân vật được lưu vào file
 * 
 * Hàm kiểm tra xem người chơi đã tồn tại trong danh sách chưa, nếu chưa thì thêm vào.
 * Sau đó, tạo thư mục "Saves" (nếu chưa tồn tại) và lưu trạng thái trò chơi của người chơi vào file nhị phân.
 */
void saveGame(Node* head, const int& size, const char* username, const int& character);

/**
 * Hàm trả về giá trị lớn hơn giữa hai số nguyên
 * @param a: Số nguyên thứ nhất
 * @param b: Số nguyên thứ hai
 * @return Giá trị lớn hơn giữa `a` và `b`
 */
int max(int a, int b);

/**
 * Hàm thêm người chơi vào danh sách nếu chưa tồn tại
 * @param username: Tên người chơi cần thêm vào danh sách
 * @param playersFile: Đường dẫn đến file lưu danh sách người chơi
 * 
 * Hàm kiểm tra xem người chơi đã tồn tại trong danh sách chưa. Nếu chưa, 
 * tên người chơi sẽ được ghi thêm vào file nhị phân theo định dạng: 
 * trước tiên ghi độ dài tên, sau đó ghi nội dung tên.
 */
void addPlayerToList(const char* username, const char* playersFile);

/**
 * Hàm đọc bảng xếp hạng từ file nhị phân
 * @param filePath: Đường dẫn đến file lưu bảng xếp hạng
 * @param players: Mảng con trỏ lưu tên các người chơi (được cấp phát động)
 * @param scores: Mảng lưu điểm số tương ứng của từng người chơi
 * @return Số lượng người chơi được đọc từ file. Trả về 0 nếu file không tồn tại.
 * 
 * Hàm mở file nhị phân, đọc số lượng người chơi, sau đó cấp phát động mảng `players`
 * và `scores` để lưu tên cùng điểm số. Dữ liệu được đọc tuần tự theo định dạng:
 * [số lượng người chơi] [độ dài tên 1] [tên 1] [điểm 1] ... [độ dài tên N] [tên N] [điểm N].
 */
int readLeaderboard(const char* filePath, char**& players, int*& scores);

/**
 * Hàm ghi bảng xếp hạng vào file nhị phân
 * @param filePath: Đường dẫn đến file lưu bảng xếp hạng
 * @param players: Mảng con trỏ chứa tên các người chơi
 * @param scores: Mảng chứa điểm số tương ứng của từng người chơi
 * @param curBoardSize: Số lượng người chơi trong bảng xếp hạng
 * 
 * Hàm mở file ở chế độ ghi nhị phân và ghi toàn bộ dữ liệu bảng xếp hạng.
 * File sẽ được ghi lại từ đầu (xoá dữ liệu cũ), theo định dạng:
 * [số lượng người chơi] [độ dài tên 1] [tên 1] [điểm 1] ... [độ dài tên N] [tên N] [điểm N].
 */
void writeLeaderboard(const char* filePath, char** players, const int* scores, int curBoardSize);

/**
 * Hàm cập nhật điểm số của người chơi hoặc thêm người chơi mới vào bảng xếp hạng
 * @param players Mảng con trỏ chứa danh sách tên người chơi
 * @param scores Mảng chứa điểm số tương ứng của từng người chơi
 * @param curBoardSize Số lượng người chơi hiện tại trong bảng xếp hạng
 * @param username Tên người chơi cần cập nhật hoặc thêm mới
 * @param point Điểm số của người chơi cần cập nhật hoặc thêm mới
 * 
 * Hàm kiểm tra xem người chơi đã tồn tại trong danh sách hay chưa. Nếu đã tồn tại, 
 * điểm số sẽ được cập nhật nếu lớn hơn điểm cũ. Nếu chưa tồn tại, người chơi mới 
 * sẽ được thêm vào danh sách cùng với điểm số của họ.
 */
void updateOrAddPlayer(char**& players, int*& scores, int& curBoardSize, const char* username, int point);

/**
 * Hàm sắp xếp bảng xếp hạng theo thứ tự giảm dần của điểm số.
 * @param players: Mảng con trỏ chứa danh sách tên người chơi.
 * @param scores: Mảng chứa điểm số tương ứng của từng người chơi.
 * @param curBoardSize: Số lượng người chơi trong bảng xếp hạng.
 * 
 * Hàm sử dụng thuật toán sắp xếp lựa chọn (selection sort) để tìm vị trí có điểm cao nhất
 * và đổi chỗ với phần tử hiện tại, đảm bảo bảng xếp hạng được sắp xếp theo thứ tự giảm dần.
 */
void sortLeaderboard(char** players, int* scores, int curBoardSize);

/**
 * Hàm hiển thị bảng xếp hạng và cập nhật điểm số của người chơi.
 * @param window: Đối tượng cửa sổ SFML để hiển thị giao diện.
 * @param font: Phông chữ sử dụng để hiển thị bảng xếp hạng.
 * @param size: Kích thước bảng trò chơi, được sử dụng để xác định file leaderboard tương ứng.
 * @param username: Tên người chơi cần cập nhật điểm số trong bảng xếp hạng.
 * @param point: Điểm số của người chơi cần cập nhật trong bảng xếp hạng.
 * 
 * Hàm thực hiện các bước sau:
 *  - Xác định đường dẫn đến file danh sách người chơi và bảng xếp hạng.
 *  - Đảm bảo người chơi tồn tại trong danh sách bằng cách gọi hàm addPlayerToList.
 *  - Đọc dữ liệu bảng xếp hạng từ file thông qua hàm readLeaderboard.
 *  - Cập nhật hoặc thêm người chơi mới vào bảng xếp hạng bằng hàm updateOrAddPlayer.
 *  - Sắp xếp bảng xếp hạng theo thứ tự giảm dần dựa trên điểm số bằng hàm sortLeaderboard.
 *  - Ghi lại bảng xếp hạng cập nhật vào file bằng hàm writeLeaderboard.
 *  - Hiển thị bảng xếp hạng trên cửa sổ game bằng hàm displayLeaderboard.
 *  - Giải phóng bộ nhớ đã cấp phát cho mảng lưu danh sách người chơi và điểm số.
 */
void leaderboard(sf::RenderWindow& window, const sf::Font& font, const int& size, const char* username, const int& point);



// /* ================= FreeMemory.CPP ================= */



/**
 * Hàm giải phóng bộ nhớ cho bảng trò chơi, danh sách liên kết và tên người chơi.
 * 
 * @param bang Con trỏ cấp 2 đại diện cho bảng trò chơi.
 * @param size Kích thước của bảng trò chơi.
 * @param head Con trỏ đến node đầu tiên của danh sách liên kết lưu trạng thái trò chơi.
 * @param username Con trỏ chứa tên người chơi.
 * 
 * Hàm này giải phóng bộ nhớ đã được cấp phát cho:
 * - Mảng 2 chiều `bang` (bảng trò chơi).
 * - Danh sách liên kết `head` (bao gồm cả mảng gameState trong mỗi node).
 * - Chuỗi ký tự `username`.
 * Sau khi giải phóng, các con trỏ được đặt về nullptr để tránh truy cập bộ nhớ không hợp lệ.
 */
void freeMemory(int**& bang, const int& size, Node*& head, char*& username);



// /* ================= Game.CPP ================= */



/**
 * Constructor của lớp Game.
 * 
 * Hàm tạo Game thực hiện các bước khởi tạo sau:
 * - Tải font chữ từ file được chỉ định.
 * - Tạo cửa sổ trò chơi với kích thước 800x600, tiêu đề "2048 Game" và kiểu cửa sổ chỉ cho phép đóng qua Titlebar và nút Close.
 * - Đặt giới hạn khung hình là 60 FPS.
 * - Khởi tạo trạng thái undo/redo bằng cách tạo node đầu tiên của danh sách liên kết.
 */
//Game::Game()

/**
 * Destructor của lớp Game.
 * 
 * Hàm hủy của lớp Game giải phóng bộ nhớ đã được cấp phát cho:
 * - Bảng trò chơi (mảng 2 chiều `bang`)
 * - Danh sách liên kết lưu trạng thái undo/redo (`head`)
 * - Tên người chơi (`player.username`)
 */
//Game::~Game()

/**
 * Hàm chạy chính của trò chơi.
 * 
 * Hàm run() của lớp Game quản lý vòng lặp chính của trò chơi, bao gồm các chức năng:
 * - Kiểm tra cửa sổ game có mở không.
 * - Tạo game mới nếu người chơi chọn (isNewGame).
 * - Hiển thị giao diện chơi game (playWindow).
 * - Xử lý các thao tác của người chơi:
 *   + Hiển thị lưới trò chơi (printGrid).
 *   + Nhận và xử lý đầu vào bàn phím (control) để thực hiện các thao tác:
 *     - Di chuyển: hợp nhất hàng (mergeRow) hoặc cột (mergeCol) dựa trên phím nhấn.
 *     - Thao tác undo/redo (undo, redo) và cập nhật điểm số.
 *     - Lưu trò chơi (saveGame) hoặc thoát trò chơi khi cần.
 *   + Thêm số ngẫu nhiên vào bảng (randNumber) và cập nhật trạng thái mới (newState).
 * - Kiểm tra điều kiện thắng (winCheck) hoặc thua (loseCheck) của trò chơi.
 * - Hiển thị màn hình thắng (winScreen) hoặc thua (loseScreen) và xử lý các lựa chọn tiếp theo:
 *   + Nếu thắng: cho phép người chơi tiếp tục hoặc cập nhật bảng xếp hạng.
 *   + Nếu thua: cho phép người chơi chơi lại hoặc thoát.
 * - Cập nhật và hiển thị bảng xếp hạng (leaderboard) khi trò chơi kết thúc.
 * 
 * Hàm sử dụng các biến thành viên của lớp Game (như window, font, bang, size, head, currentNode, player, v.v.) 
 * để quản lý trạng thái và dữ liệu của trò chơi.
 */
//void Game::run()



// /* ================= GameLogic.CPP ================= */



/**
 * Hàm tạo và khởi tạo bảng trò chơi mới.
 * 
 * Hàm makeGrid tạo một mảng 2 chiều với kích thước được chỉ định, khởi tạo tất cả các phần tử 
 * với giá trị 0 và sau đó đặt một giá trị ngẫu nhiên (2 hoặc 4) vào một vị trí ngẫu nhiên trên bảng.
 * - Giá trị 4 được đặt với xác suất 10% (nếu numberChance == 1), ngược lại giá trị 2 được đặt.
 * - Vị trí được chọn bằng cách sử dụng hàm rand() với seed là thời gian hiện tại.
 * 
 * @param size Kích thước của bảng trò chơi (số hàng và số cột).
 * @return Con trỏ cấp 2 đại diện cho bảng trò chơi đã được khởi tạo.
 */
int** makeGrid(const int& size);

/**
 * Hàm thêm một số ngẫu nhiên vào một ô trống trên bảng trò chơi.
 * 
 * @param bang Mảng 2 chiều đại diện cho bảng trò chơi.
 * @param size Kích thước của bảng trò chơi (số hàng và số cột).
 * 
 * Hàm này thực hiện các bước sau:
 * - Sinh số ngẫu nhiên từ 1 đến 10 để quyết định số được thêm (4 với xác suất 10%, 2 với xác suất 90%).
 * - Duyệt qua bảng trò chơi để tìm tất cả các ô trống (ô có giá trị 0) và lưu tọa độ của chúng vào mảng tạm thời.
 * - Nếu không còn ô trống nào, giải phóng bộ nhớ của mảng tạm thời và kết thúc hàm.
 * - Chọn ngẫu nhiên một ô trống từ danh sách và gán số đã chọn vào ô đó.
 * - Giải phóng bộ nhớ của mảng tạm thời.
 */
void randNumber(int** bang, const int& size);

/**
 * Hàm thực hiện thao tác gộp các số trong hàng của bảng trò chơi theo hướng được chỉ định.
 * 
 * @param bang Mảng 2 chiều đại diện cho bảng trò chơi.
 * @param size Kích thước của bảng trò chơi (số hàng và số cột).
 * @param button Phím được nhấn để xác định hướng gộp hàng. Nếu là sf::Keyboard::A hoặc sf::Keyboard::Left,
 *               thực hiện thao tác gộp theo hướng trái; nếu là sf::Keyboard::D hoặc sf::Keyboard::Right,
 *               thực hiện thao tác gộp theo hướng phải.
 * 
 * Hàm này thực hiện các bước sau:
 * - Duyệt qua từng hàng của bảng trò chơi.
 * - Nếu hướng gộp là bên trái:
 *   + Dồn tất cả các số khác 0 về phía bên trái của hàng.
 *   + Gộp các số giống nhau liên tiếp từ trái qua phải (nhân đôi giá trị số bên trái và đặt giá trị bên phải bằng 0).
 *   + Dồn lại các số đã được gộp về phía bên trái.
 * - Nếu hướng gộp là bên phải:
 *   + Dồn tất cả các số khác 0 về phía bên phải của hàng.
 *   + Gộp các số giống nhau liên tiếp từ phải qua trái (nhân đôi giá trị số bên phải và đặt giá trị bên trái bằng 0).
 *   + Dồn lại các số đã được gộp về phía bên phải.
 */
void mergeRow(int** bang, const int& size, const char& button);

/**
 * Hàm thực hiện thao tác gộp các số theo cột của bảng trò chơi dựa trên hướng được chỉ định.
 * 
 * @param bang Mảng 2 chiều đại diện cho bảng trò chơi.
 * @param size Kích thước của bảng trò chơi (số hàng và số cột).
 * @param button Phím được nhấn để xác định hướng gộp cột. Nếu là sf::Keyboard::W hoặc sf::Keyboard::Up,
 *               thực hiện thao tác gộp theo hướng lên; nếu không, thực hiện thao tác gộp theo hướng xuống.
 * 
 * Hàm này thực hiện các bước sau:
 * - Duyệt qua từng cột của bảng trò chơi.
 * - Nếu hướng gộp là lên:
 *   + Dồn các số khác 0 về phía trên của cột.
 *   + Gộp các số giống nhau liên tiếp từ trên xuống dưới (nhân đôi giá trị ở vị trí trên và đặt giá trị ở vị trí dưới bằng 0).
 *   + Dồn lại các số đã được gộp về phía trên.
 * - Nếu hướng gộp là xuống:
 *   + Dồn các số khác 0 về phía dưới của cột.
 *   + Gộp các số giống nhau liên tiếp từ dưới lên trên (nhân đôi giá trị ở vị trí dưới và đặt giá trị ở vị trí trên bằng 0).
 *   + Dồn lại các số đã được gộp về phía dưới.
 */
void mergeCol(int** bang, const int& size, const char& button);

/**
 * Hàm kiểm tra điều kiện thắng của trò chơi.
 * 
 * @param bang Mảng 2 chiều đại diện cho bảng trò chơi.
 * @param size Kích thước của bảng trò chơi (số hàng và số cột).
 * @param afterWin Biến cờ cho biết liệu trò chơi đang ở chế độ chơi tiếp sau khi thắng hay không.
 * @return true Nếu tồn tại ô nào có giá trị 2048 và không đang ở chế độ chơi tiếp sau thắng.
 * @return false Nếu không tìm thấy ô nào có giá trị 2048 hoặc nếu trò chơi đang ở chế độ chơi tiếp sau thắng.
 * 
 * Hàm này duyệt qua toàn bộ bảng trò chơi để xác định xem có ô nào đạt giá trị 2048 không.
 * Nếu biến afterWin được bật (true), hàm sẽ bỏ qua kiểm tra thắng và trả về false, 
 * cho phép người chơi tiếp tục chơi ngay cả khi đã đạt giá trị 2048.
 */
bool winCheck(int** bang, const int& size, const bool& afterWin);

/**
 * Hàm kiểm tra điều kiện thua của trò chơi.
 * 
 * @param bang Mảng 2 chiều đại diện cho bảng trò chơi.
 * @param size Kích thước của bảng trò chơi (số hàng và số cột).
 * @return true Nếu không còn ô trống và không thể gộp các ô nào (trò chơi đã thua).
 * @return false Nếu còn ít nhất một ô trống hoặc có khả năng gộp các ô (trò chơi chưa thua).
 * 
 * Hàm này duyệt qua từng ô trong bảng trò chơi để kiểm tra:
 * - Nếu tồn tại ô trống (giá trị 0), trò chơi chưa thua.
 * - Nếu có ô nào có giá trị bằng với ô bên dưới hoặc bên phải, nghĩa là vẫn có thể gộp các ô,
 *   trò chơi chưa thua.
 * Nếu không thỏa cả hai điều kiện trên, hàm trả về true, báo hiệu người chơi đã thua.
 */
bool loseCheck(int** bang, const int& size);

/**
 * Hàm tính tổng điểm của bảng trò chơi.
 * 
 * @param bang Mảng 2 chiều đại diện cho bảng trò chơi.
 * @param size Kích thước của bảng trò chơi (số hàng và số cột).
 * @return Tổng điểm của bảng trò chơi, được tính bằng tổng các giá trị trong mỗi ô của ma trận.
 * 
 * Hàm này duyệt qua tất cả các ô trong ma trận và cộng giá trị của từng ô vào biến điểm.
 */
int score(int** bang, const int& size);



// /* ================= Graphics.CPP ================= */



/**
 * Hàm xác định màu nền cho ô trò chơi dựa trên giá trị của nó.
 * 
 * @param number Giá trị số trong ô trò chơi.
 * @return sf::Color Màu nền tương ứng với giá trị.
 */
sf::Color cellColor(const int& number);

/**
 * Hàm lấy màu chữ cho số trong ô dựa trên giá trị của số.
 * 
 * @param number Giá trị số trong ô trò chơi.
 * @return sf::Color Màu chữ tương ứng:
 *         - Nếu giá trị là 2 hoặc 4, trả về sf::Color(119, 110, 101).
 *         - Với các giá trị khác, trả về sf::Color(255, 255, 255).
 */
sf::Color numberColor(const int& number);

/**
 * Hàm hiển thị màn hình chào mừng của trò chơi.
 * 
 * @param window Đối tượng cửa sổ SFML dùng để hiển thị giao diện.
 * @param font Phông chữ được sử dụng để hiển thị tiêu đề và hướng dẫn trên màn hình.
 * 
 * Hàm printWelcomeScreen thực hiện các bước sau:
 * - Tạo và cấu hình tiêu đề trò chơi "2048 Game" với kích thước font 60, căn giữa theo chiều ngang và đặt vị trí khoảng 1/3 chiều cao cửa sổ.
 * - Tạo văn bản hướng dẫn "Press Any Key Or Click To Continue..." với kích thước font 30, căn giữa theo chiều ngang và đặt vị trí khoảng 1/2 chiều cao cửa sổ.
 * - Vào vòng lặp sự kiện, xử lý các sự kiện:
 *   + Nếu nhận sự kiện đóng cửa sổ (Closed), đóng cửa sổ và thoát chương trình.
 *   + Nếu nhận bất kỳ phím nào được nhấn hoặc sự kiện click chuột trái, thoát khỏi hàm và kết thúc màn hình chào mừng.
 * - Liên tục vẽ và cập nhật màn hình với tiêu đề và văn bản hướng dẫn cho đến khi có sự kiện thoát.
 */
void printWelcomeScreen(sf::RenderWindow& window, const sf::Font& font);

/**
 * Hàm hiển thị menu chính của trò chơi và xử lý lựa chọn của người dùng.
 * 
 * @param window Đối tượng cửa sổ SFML để hiển thị giao diện menu.
 * @param font Phông chữ sử dụng để hiển thị tiêu đề và các mục menu.
 * @return int Lựa chọn của người dùng:
 *         - 1: "Bắt đầu trò chơi mới"
 *         - 2: "Tiếp tục trò chơi cũ"
 *         - -1: Nếu cửa sổ bị đóng hoặc người dùng thoát menu.
 * 
 * Hàm này thực hiện các bước sau:
 * - Tạo tiêu đề "2048 Game" và căn giữa nó trên cửa sổ.
 * - Tạo hai mục menu: "Bắt đầu trò chơi mới" và "Tiếp tục trò chơi cũ", cùng căn giữa và định vị phù hợp.
 * - Xử lý các sự kiện từ người dùng:
 *   + Nếu cửa sổ bị đóng, trả về -1.
 *   + Nếu chuột di chuyển, cập nhật mục được chọn dựa trên vị trí chuột.
 *   + Nếu nhấn phím mũi tên (hoặc W/S), chuyển đổi lựa chọn giữa các mục.
 *   + Nếu nhấn phím Enter hoặc click chuột trái vào một mục menu, trả về lựa chọn tương ứng.
 * - Vẽ và cập nhật giao diện menu liên tục cho đến khi người dùng đưa ra lựa chọn.
 */
int Menu(sf::RenderWindow& window, const sf::Font& font);

/**
 * Hàm hiển thị giao diện nhập tên người chơi và xử lý đầu vào từ bàn phím.
 * 
 * @param window Đối tượng cửa sổ SFML để hiển thị giao diện nhập tên.
 * @param font Phông chữ được sử dụng để hiển thị hướng dẫn và hộp nhập tên.
 * @param username Mảng ký tự lưu trữ tên người chơi được nhập. Chuỗi này sẽ được cập nhật khi người chơi nhập.
 * 
 * Hàm này thực hiện các bước sau:
 * - Khởi tạo chuỗi username thành chuỗi rỗng.
 * - Hiển thị hướng dẫn nhập tên "Nhap ten nguoi choi (khong co khoang trang):" và tạo một hộp nhập tên.
 * - Lắng nghe và xử lý sự kiện từ bàn phím:
 *   + Nếu người dùng nhấn phím Backspace, xóa ký tự cuối cùng của chuỗi username.
 *   + Nếu người dùng nhấn Enter, kiểm tra tính hợp lệ của chuỗi (không rỗng và không chứa khoảng trắng) và kết thúc việc nhập.
 *   + Chỉ chấp nhận ký tự ASCII và đảm bảo không vượt quá giới hạn của mảng (MAXLEN).
 * - Liên tục cập nhật và vẽ giao diện nhập tên cho đến khi người dùng xác nhận tên.
 */
void nameInput(sf::RenderWindow& window, const sf::Font& font, char* username);

/**
 * Hàm hiển thị giao diện chọn nhân vật cho trò chơi và xử lý đầu vào của người dùng.
 * 
 * @param window Đối tượng cửa sổ SFML dùng để hiển thị giao diện.
 * @param font Phông chữ được sử dụng để hiển thị văn bản và hình ảnh.
 * @return int Chỉ số của nhân vật được chọn (từ 1 đến 5), hoặc -1 nếu cửa sổ bị đóng.
 * 
 * Hàm characterChoose thực hiện các bước sau:
 * - Hiển thị tiêu đề "Nhan vat" ở phần trên của cửa sổ.
 * - Nạp các file ảnh của 5 nhân vật khác nhau và tạo sprite tương ứng.
 * - Hiển thị mũi tên trái và phải để người dùng có thể chuyển đổi giữa các nhân vật.
 * - Tạo nút "Choose" cho phép người dùng xác nhận lựa chọn nhân vật.
 * - Xử lý các sự kiện từ chuột và bàn phím để cập nhật nhân vật được chọn:
 *   + Nếu nhấn chuột vào mũi tên, thay đổi chỉ số nhân vật được chọn.
 *   + Nếu nhấn Enter hoặc nhấn chuột vào nút "Choose", trả về chỉ số của nhân vật được chọn.
 * - Liên tục cập nhật giao diện cho đến khi người dùng xác nhận lựa chọn hoặc cửa sổ bị đóng.
 */
int characterChoose(sf::RenderWindow& window, const sf::Font& font);

/**
 * Hàm hiển thị menu hỏi người dùng có muốn quay lại hay không.
 * 
 * @param window Đối tượng cửa sổ SFML để hiển thị menu.
 * @param font Phông chữ được sử dụng để hiển thị văn bản trong menu.
 * @return int Trả về:
 *         - 1 nếu người dùng chọn "Co" (có muốn quay lại),
 *         - 2 nếu người dùng chọn "Khong" (không muốn quay lại),
 *         - -1 nếu cửa sổ bị đóng.
 * 
 * Hàm Return hiển thị một menu với tiêu đề "Ban co muon quay lai ?" và hai lựa chọn "Co" và "Khong".
 * Người dùng có thể lựa chọn bằng cách di chuyển chuột, nhấn các phím mũi tên (hoặc W/S) hoặc click chuột.
 * Khi lựa chọn được xác nhận (nhấn Enter hoặc click chuột), hàm trả về lựa chọn tương ứng.
 */
int Return(sf::RenderWindow& window, const sf::Font& font);

/**
 * Hàm hiển thị giao diện nhập kích thước tùy chỉnh.
 * 
 * @param window Đối tượng cửa sổ SFML để hiển thị giao diện nhập.
 * @param font Phông chữ được sử dụng để hiển thị văn bản trong giao diện.
 * @return int Giá trị kích thước được nhập bởi người dùng. Trả về -1 nếu cửa sổ bị đóng.
 * 
 * Hàm customizeSize tạo một hộp nhập và xử lý các sự kiện bàn phím để cho phép người dùng nhập vào
 * một chuỗi số (không chứa khoảng trắng) nhằm tùy chỉnh kích thước trò chơi. Người dùng có thể sử dụng
 * phím Backspace để xóa ký tự cuối cùng và nhấn Enter để xác nhận lựa chọn. Sau khi hoàn tất, chuỗi ký tự
 * được chuyển thành số nguyên và trả về.
 */
int customizeSize(sf::RenderWindow& window, const sf::Font& font);

/**
 * Hàm hiển thị menu nhập kích thước trò chơi và xử lý lựa chọn của người dùng.
 * 
 * @param window Đối tượng cửa sổ SFML dùng để hiển thị giao diện menu.
 * @param font Phông chữ được sử dụng để hiển thị tiêu đề và các mục menu.
 * @return int Giá trị kích thước trò chơi được chọn:
 *         - 4 nếu người dùng chọn "4 x 4"
 *         - 6 nếu người dùng chọn "6 x 6"
 *         - Một giá trị tùy chỉnh nếu người dùng chọn "Khac" và nhập một số hợp lệ (số > 4, khác 6, và phù hợp với yêu cầu trải nghiệm chơi tốt)
 *         - -1 nếu cửa sổ bị đóng hoặc xảy ra lỗi.
 * 
 * Hàm sizeInput hiển thị một menu với ba lựa chọn:
 * - "4 x 4"
 * - "6 x 6"
 * - "Khac" (tùy chỉnh)
 * Người dùng có thể di chuyển giữa các lựa chọn bằng cách sử dụng chuột hoặc bàn phím (phím Up, Down, W, S)
 * và xác nhận lựa chọn bằng cách nhấn Enter hoặc click chuột trái. Nếu lựa chọn "Khac" được chọn,
 * hàm sẽ cho phép nhập một chuỗi số (chỉ chấp nhận ký tự số và không chứa khoảng trắng) và chuyển đổi chuỗi đó thành số nguyên.
 */
int sizeInput(sf::RenderWindow& window, const sf::Font& font);

/**
 * Hàm cập nhật kích thước cửa sổ và chế độ nhìn (view) dựa trên kích thước của bảng trò chơi.
 * 
 * @param window Đối tượng cửa sổ SFML để hiển thị giao diện trò chơi.
 * @param size Số hàng (và cột) của bảng trò chơi.
 * 
 * Hàm playWindow thực hiện các bước sau:
 * - Xác định kích thước ô cơ sở (baseCellSize) và tính toán kích thước ô (cellSize) dựa trên giá trị của size.
 *   Nếu size >= 9, kích thước ô được giảm tỷ lệ (8.0 / size) so với baseCellSize.
 * - Tính toán kích thước tổng thể của bảng chơi (playSize = size * cellSize).
 * - Thay đổi kích thước cửa sổ để đảm bảo bảng chơi và các giao diện phụ (ví dụ: điểm số, điều khiển, ...)
 *   có đủ không gian, với một số khoảng cách bổ sung (250 pixel chiều rộng và 150 pixel chiều cao).
 * - Căn giữa cửa sổ trên màn hình dựa trên độ phân giải màn hình hiện tại.
 * - Cập nhật chế độ nhìn (view) của cửa sổ để giữ tỷ lệ hiển thị nội dung, đảm bảo nội dung không bị méo.
 */
void playWindow(sf::RenderWindow& window, const int &size);

/**
 * Hàm vẽ bảng trò chơi và các thông tin liên quan lên cửa sổ.
 * 
 * @param window Đối tượng cửa sổ SFML để hiển thị giao diện trò chơi.
 * @param font Phông chữ được sử dụng để vẽ chữ trên bảng.
 * @param bang Mảng 2 chiều chứa trạng thái của bảng trò chơi (giá trị từng ô).
 * @param size Số hàng (và cột) của bảng trò chơi.
 * @param character Số thứ tự của nhân vật được chọn (1 đến 5).
 * 
 * Hàm printGrid thực hiện các bước sau:
 * - Điều chỉnh kích thước ô và kích thước chữ dựa trên kích thước bảng trò chơi.
 * - Xóa cửa sổ và thiết lập màu nền.
 * - Vẽ từng ô vuông của bảng:
 *   + Tạo hình chữ nhật cho mỗi ô với kích thước đã tính toán.
 *   + Đặt vị trí và màu nền của ô dựa trên giá trị trong ô (sử dụng hàm cellColor).
 *   + Nếu ô không chứa giá trị 0, hiển thị số trong ô được căn giữa.
 * - Tính điểm của người chơi dựa trên tổng các giá trị trong bảng (sử dụng hàm score) và hiển thị điểm.
 * - Tải và hiển thị hình ảnh nhân vật tương ứng với lựa chọn của người chơi.
 * - Vẽ khung chứa điểm và các thông tin điều khiển:
 *   + Hiển thị các hướng dẫn về phím bấm: New game, điều khiển di chuyển, undo/redo, thoát hoặc lưu và thoát.
 * - Cập nhật cửa sổ hiển thị.
 */
void printGrid(sf::RenderWindow& window, const sf::Font& font, int** bang, const int& size, const int& character);

/**
 * Hàm hiển thị màn hình chiến thắng và xử lý lựa chọn của người dùng sau khi thắng.
 * 
 * @param window Đối tượng cửa sổ SFML để hiển thị giao diện.
 * @param font Phông chữ được sử dụng để hiển thị văn bản trên màn hình chiến thắng.
 * @return int Trả về:
 *         - 1 nếu người dùng chọn "Có" (muốn chơi tiếp),
 *         - 2 nếu người dùng chọn "Không" (không muốn chơi tiếp),
 *         - -1 nếu cửa sổ bị đóng.
 * 
 * Hàm winScreen hiển thị tiêu đề "Ban da thang" và câu hỏi "Ban co muon choi tiep khong ?",
 * cùng với hai lựa chọn "Co" và "Khong". Người dùng có thể lựa chọn bằng cách di chuyển chuột,
 * sử dụng phím mũi tên (Up, Down, W, S) hoặc nhấn Enter, cũng như click chuột trái. Khi người dùng xác nhận lựa chọn,
 * hàm trả về giá trị tương ứng để chỉ ra hành động tiếp theo của người chơi.
 */
int winScreen(sf::RenderWindow& window, const sf::Font& font);

/**
 * Hàm hiển thị màn hình thua và xử lý lựa chọn của người dùng sau khi thua.
 * 
 * @param window Đối tượng cửa sổ SFML để hiển thị giao diện.
 * @param font Phông chữ được sử dụng để hiển thị văn bản.
 * @param bang Mảng 2 chiều chứa trạng thái của bảng trò chơi.
 * @param size Số hàng (và cột) của bảng trò chơi.
 * @param character Số thứ tự của nhân vật được chọn (dùng để hiển thị hình nhân vật).
 * @return int Trả về:
 *         - 1 nếu người dùng chọn "Co" (muốn chơi mới),
 *         - 2 nếu người dùng chọn "Khong" (không muốn chơi mới),
 *         - -1 nếu cửa sổ bị đóng.
 * 
 * Hàm loseScreen thực hiện các bước sau:
 * - Tạo hiệu ứng mờ (blur) trên toàn cửa sổ bằng cách vẽ một hình chữ nhật bán trong suốt.
 * - Hiển thị tiêu đề "GAME OVER" và bàn cờ hiện tại (bằng cách gọi hàm printGrid).
 * - Chờ người dùng thực hiện thao tác (nhấn phím hoặc click chuột) để tiến hành.
 * - Sau đó, hiển thị câu hỏi "Ban co muon choi moi khong ?" cùng với hai lựa chọn "Co" và "Khong".
 * - Đợi các sự kiện từ bàn phím và chuột để cập nhật lựa chọn và trả về lựa chọn của người dùng.
 */
int loseScreen(sf::RenderWindow& window, const sf::Font& font, int** bang, const int& size, const int& character);

/**
 * Hàm hiển thị bảng xếp hạng người chơi trên cửa sổ.
 * 
 * @param window Đối tượng cửa sổ SFML để hiển thị bảng xếp hạng.
 * @param font Phông chữ được sử dụng để hiển thị tiêu đề và các văn bản trên bảng xếp hạng.
 * @param size Kích thước của bàn chơi (số hàng và số cột), được dùng để tạo tiêu đề bảng.
 * @param players Mảng các chuỗi ký tự chứa tên của người chơi.
 * @param scores Mảng chứa điểm số tương ứng của từng người chơi.
 * @param curBoardSize Số lượng người chơi hiện có trong bảng xếp hạng.
 * @param maxDisplay Số lượng người chơi tối đa sẽ được hiển thị trên bảng xếp hạng.
 * 
 * Hàm displayLeaderboard thực hiện các bước sau:
 * - Xóa cửa sổ và đặt màu nền.
 * - Tạo tiêu đề bảng xếp hạng theo định dạng "Leaderboard {size}x{size}".
 * - Hiển thị tiêu đề cho các cột "Username" và "Point".
 * - Xác định số lượng người chơi cần hiển thị dựa trên giá trị maxDisplay và curBoardSize.
 * - Duyệt qua danh sách người chơi và hiển thị tên cùng điểm số của từng người chơi, căn giữa theo cột.
 * - Cập nhật cửa sổ hiển thị.
 * - Chờ người dùng nhấn phím để thoát khỏi bảng xếp hạng.
 */
void displayLeaderboard(sf::RenderWindow& window, const sf::Font& font, const int& size, char** players, const int* scores, int curBoardSize, int maxDisplay);



// /* ================= NewGame.CPP ================= */



/**
 * Hàm khởi tạo trò chơi mới.
 * 
 * @param window Đối tượng cửa sổ SFML để hiển thị giao diện trò chơi.
 * @param font Phông chữ được sử dụng để hiển thị văn bản trên giao diện.
 * @param bang Con trỏ cấp 2 lưu trữ bảng trò chơi hiện tại. Nếu có trò chơi đã lưu, bảng sẽ được tải lên.
 * @param size Biến lưu kích thước bảng trò chơi (số hàng và cột).
 * @param currentNode Con trỏ đến node hiện tại của danh sách trạng thái trò chơi (undo/redo).
 * @param username Con trỏ chứa tên người chơi.
 * @param character Biến lưu thông tin nhân vật được chọn.
 * @param isNewGame Biến cờ chỉ thị xem trò chơi mới đã được khởi tạo chưa.
 * 
 * Hàm newGame thực hiện các bước sau:
 * - Hiển thị màn hình chào mừng.
 * - Yêu cầu người chơi nhập tên và lưu vào biến username.
 * - Nếu người chơi không nhập tên hoặc hủy nhập, giải phóng bộ nhớ và thoát chương trình.
 * - Tải trò chơi đã lưu (nếu có) từ file thông qua hàm loadSave.
 * - Nếu không có trò chơi đã lưu:
 *   + Yêu cầu người chơi chọn nhân vật qua hàm characterChoose.
 *   + Nếu người chơi hủy việc chọn nhân vật, giải phóng bộ nhớ và thoát chương trình.
 *   + Yêu cầu người chơi nhập kích thước bảng qua hàm sizeInput.
 *   + Nếu người chơi hủy nhập kích thước, giải phóng bộ nhớ và thoát chương trình.
 *   + Tạo bảng mới với kích thước được chọn bằng hàm makeGrid.
 *   + Sinh số ngẫu nhiên đầu tiên trên bảng bằng hàm randNumber.
 * - Sao chép trạng thái bảng hiện tại vào currentNode->gameState để khởi tạo trạng thái undo/redo.
 * - Đặt cờ isNewGame thành false vì trò chơi đã được khởi tạo thành công.
 */
void newGame(sf::RenderWindow& window, const sf::Font& font, int**& bang, int& size, Node*& currentNode, char*& username, int& character, bool& isNewGame);



// /* ================= UndoRedo.CPP ================= */



/**
 * Hàm lưu trạng thái mới của bảng trò chơi vào danh sách liên kết undo/redo.
 * 
 * @param bang Mảng 2 chiều chứa trạng thái hiện tại của bảng trò chơi.
 * @param size Kích thước của bảng trò chơi (số hàng và cột).
 * @param currentNode Con trỏ đến node hiện tại trong danh sách trạng thái trò chơi.
 * 
 * Hàm newState thực hiện các bước sau:
 * - Xóa tất cả các trạng thái redo (các node sau currentNode) nếu đã thực hiện thao tác undo.
 * - So sánh trạng thái hiện tại của bảng (bang) với trạng thái được lưu trong currentNode.
 *   Nếu không có sự thay đổi, hàm kết thúc mà không lưu trạng thái mới.
 * - Nếu có sự thay đổi, tạo một node mới và sao chép toàn bộ dữ liệu của bảng (bang) vào node mới.
 * - Liên kết node mới vào danh sách trạng thái (thiết lập liên kết prev và next) và cập nhật currentNode để trỏ đến node mới.
 */
void newState(int** bang, const int& size, Node*& currentNode);

/**
 * Hàm thực hiện thao tác Undo trong trò chơi.
 * 
 * @param window Đối tượng cửa sổ SFML để hiển thị giao diện trò chơi.
 * @param font Phông chữ được sử dụng để hiển thị thông báo trên màn hình.
 * @param bang Mảng 2 chiều lưu trữ trạng thái bảng trò chơi hiện tại.
 * @param size Kích thước của bảng trò chơi (số hàng và số cột).
 * @param character Số thứ tự của nhân vật, dùng để hiển thị bảng chơi.
 * @param currentNode Con trỏ đến node hiện tại của danh sách trạng thái (undo/redo).
 * 
 * Hàm undo thực hiện các bước sau:
 * - Kiểm tra xem có thể thực hiện thao tác Undo hay không (tức là có tồn tại node trước currentNode).
 * - Nếu không có node trước, hiển thị thông báo "Khong the Undo!" trên cửa sổ, tạm dừng 0.5 giây và thoát khỏi hàm.
 * - Nếu có thể Undo, cập nhật currentNode thành node trước đó và sao chép trạng thái bảng chơi từ node đó vào mảng bang.
 */
void undo(sf::RenderWindow& window, const sf::Font& font, int** bang, const int& size, const int& character, Node*& currentNode);

/**
 * Hàm thực hiện thao tác Redo trong trò chơi.
 * 
 * @param window Đối tượng cửa sổ SFML để hiển thị giao diện trò chơi.
 * @param font Phông chữ được sử dụng để hiển thị thông báo trên màn hình.
 * @param bang Mảng 2 chiều chứa trạng thái hiện tại của bảng trò chơi.
 * @param size Kích thước của bảng trò chơi (số hàng và cột).
 * @param character Số thứ tự của nhân vật, dùng để hiển thị bảng trò chơi.
 * @param currentNode Con trỏ đến node hiện tại của danh sách trạng thái (undo/redo).
 * 
 * Hàm redo thực hiện các bước sau:
 * - Kiểm tra xem có thể thực hiện thao tác redo hay không (tức là currentNode và node sau của nó tồn tại).
 * - Nếu không thể redo, hiển thị thông báo "Khong the Redo!" lên màn hình, tạm dừng 0.5 giây để người chơi đọc thông báo,
 *   sau đó thoát khỏi hàm.
 * - Nếu có thể redo, cập nhật currentNode thành node sau đó và sao chép trạng thái bảng trò chơi từ gameState của node đó vào mảng bang.
 */
void redo(sf::RenderWindow &window, const sf::Font& font, int** bang, const int& size, const int& character, Node*& currentNode);

#endif