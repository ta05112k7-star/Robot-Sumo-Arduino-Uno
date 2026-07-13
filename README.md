DỰ ÁN ROBOTSUMO 
I.GIỚI THIỆU
1.Bối cảnh
- Dự án Sumo Robot là bài tập lớn cuối học phần môn AET2021 - Thí nghiệm trong khoa học kỹ thuật 1 (chuyên ngành Lập trình nhúng & IoT). Đây là một sân chơi kỹ thuật đòi hỏi sinh viên phải vận dụng tổng hợp các kiến thức đã học để giải quyết bài toán thức tế thông qua chế tạo 1 robot tự vận hành hoàn chỉnh.

2.Phạm vi
- Dự án tập trung vào việc phát triển một robot tự vận hành hoàn toàn (không điều khiển bằng tay) trong khuôn khổ hạng mục mini-sumo. Robot phải tuân thủ nghiêm ngặt các giới hạn về kích thước (không quá 12 x 12 cm) và khối lượng (tối đa 700 g). Mọi thiết kế phải đảm bảo an toàn, không có các cơ cấu gây phá hủy đối thủ hoặc làm bẩn sàn đấu.

3.Mục tiêu
- Về cơ khí: Thành thạo việc thiết kế và chế tạo khung vỏ robot bằng công nghệ in 3D hoặc cắt laser, đảm bảo các yếu tố về độ bền, trọng tâm và lực bám.
- Về phần cứng: Tự thiết kế và tích hợp mạch điều khiển động cơ DC, mạch nguồn pin Li-ion 2S và hệ thống cảm biến.
- Về phần mềm: Lập trình firmware cho vi điều khiển (như Arduino, STM32 hoặc ESP32) theo mô hình máy trạng thái để robot có thể tự động dò biên, phát hiện đối thủ và ra quyết định tấn công/phòng thủ.
- Về kỹ năng: Rèn luyện khả năng quản lý dự án, làm việc nhóm và sử dụng các công cụ chuyên nghiệp như GitHub để quản lý mã nguồn.

4. Thành viên trong nhóm
Dương Việt Hoàng - Nhóm trưởng -Chịu trách nhiệm tổng thể về tiến độ, thiết kế mô hình 3D trên Fusion 360, căn chỉnh kích thước cơ khí, xuất file STL và tiến hành in 3D vỏ máy tại Lab; thiết kế sơ đồ đấu dây nguyên lý.
Nguyễn Đăng Anh - Thành viên - Xây dựng cấu trúc máy trạng thái hữu hạn (FSM) trên Arduino IDE, lập trình giải thuật ưu tiên xử lý ngắt cho cảm biến dò line, tối ưu hóa các hàm băm điều khiển góc quay động cơ.
Nguyễn Vân Tuấn Anh- Thành viên - Thiết lập các kịch bản thử nghiệm (Test cases) trên sa bàn thực tế, đo đạc tốc độ và dòng tải động cơ, thu thập số liệu sai số cảm biến, tổng hợp nội dung viết báo cáo kỹ thuật.
Phạm Tuấn Minh - Thành viên - Cấu hình và đọc xung thời gian phản hồi của cảm biến siêu âm HY-SRF05, lập trình bộ lọc trung bình động loại bỏ nhiễu khoảng cách, thực hiện hàn mạch và kiểm tra sụt áp nguồn nuôi.

II. TỔNG QUAN DỰ ÁN
1.Luật robot sumo
- Trận đấu diễn ra trên sàn Dohyo hình tròn có đường kính 77 cm, làm bằng gỗ MDF hoặc mica đen nhám với vạch viền trắng rộng 2.5 cm quanh mép ngoài.
- Thể thức: Thi đấu loại trực tiếp (knockout) theo sơ đồ nhánh cây; mỗi trận đấu theo thể thức Best of 3 (thắng 2 trên 3 hiệp).
- Vận hành: Robot phải có chế độ trễ 5 giây sau khi nhấn nút khởi động mới được phép di chuyển.
- Điều kiện thắng: Một hiệp kết thúc khi một robot bị đẩy ra khỏi vạch trắng hoặc tự di chuyển ra ngoài.

2.Thiết kế tham khảo
* Dựa trên yêu cầu của học phần, thiết kế robot thường bao gồm các thành phần cơ bản sau:
- Vi điều khiển: Ưu tiên sử dụng Arduino (Uno/Nano), STM32 hoặc ESP32.
- Động cơ & Driver: Sử dụng động cơ DC (có hộp số) kết hợp với các mạch công suất như L298N, TB6612 hoặc BTS7960.
- Cảm biến: Cần ít nhất 2 cảm biến dò biên (IR phản xạ) ở mép trước và các cảm biến phát hiện đối thủ như siêu âm (HC-SR04) hoặc cảm biến khoảng cách ToF.
- Khung vỏ: Được thiết kế trên phần mềm Fusion 360 và gia công từ vật liệu nhựa PLA/ABS (in 3D).

3.Cơ sở lý thuyết 
* Dự án dựa trên sự kết hợp của ba nền tảng kỹ thuật chính:
- Vật lý & Cơ khí: Áp dụng nguyên lý ma sát và trọng tâm; trong đó lực đẩy của robot tỷ lệ thuận với trọng lượng, do đó việc tối ưu khối lượng sát mức 700g và hạ thấp trọng tâm là yếu tố then chốt.
- Điện tử: Thiết kế mạch nguồn ổn định từ pin Li-ion 2S (7.4V) và xử lý tín hiệu từ cảm biến để đưa về vi điều khiển.
- Thuật toán điều khiển: Sử dụng lý thuyết về máy trạng thái hữu hạn để xây dựng các kịch bản phản xạ cho robot (Ví dụ: Trạng thái Tìm kiếm -> Trạng thái Tấn công -> Trạng thái Dò biên/Tránh khỏi vạch trắng).
