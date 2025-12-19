# Support vector machine

## Links:
- https://scikit-learn.org/stable/modules/generated/sklearn.linear_model.SGDClassifier.html
- https://scikit-learn.org/stable/modules/svm.html


## Tìm Hyperplane Suport vector machine

Sử dụng `sklearn.linear_model.SGDClassifier` với `loss='hinge'` để huấn luyện một Suport vector machine tuyến tính. Đối với tập dữ liệu 3 chiều, siêu phẳng(hyperplane) là một mặt phẳng:
```
w1*x + w2*y + w3*z + b = 0
```
Trong đó:
*   `x`, `y`, `z` là tọa độ của một điểm trong không gian 3D.
*   `w1`, `w2`, `w3` là các thành phần của vectơ weight(`w`) cho x, y và z tương ứng.
*   `b` là bias.

## Quá trình huấn luyện (SGD với Hinge Loss)

`SGDClassifier` điều chỉnh `w` và `b` lặp đi lặp lại bằng cách sử dụng **Stochastic Gradient Descent (SGD)**. Mục tiêu là tìm một siêu phẳng phân tách tốt nhất hai lớp trong tập dữ liệu.

Trong mỗi epoch, `SGDClassifier`:
1.  Lấy một mẫu(điểm dữ liệu).
2.  Dự đoán `w · x + b`.
3.  Tìm `hinge`. Mất mát hinge được định nghĩa là `max(0, 1 - y * (w · x + b))`.
4.  Tính toán gradient của hàm mất mát đối với `w` và `b`.
5.  Cập nhật `w` và `b` bằng cách di chuyển theo hướng ngược lại với gradient, được chia tỷ lệ bởi tốc độ học (`eta0`). L2 penalty (regularization) cũng được áp dụng để ngăn chặn overfitting.

