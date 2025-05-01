from sklearn.gaussian_process import GaussianProcessRegressor
from sklearn.gaussian_process.kernels import (
    ConstantKernel,
    WhiteKernel,
    RBF,
)
from sklearn.preprocessing import StandardScaler
from scipy.stats import norm

def GPDoE(x_train, y_train, x_test):
    scaler_x = StandardScaler()
    scaler_y = StandardScaler()
    scaler_x.fit(x_train)
    scaler_y.fit(y_train)
    x_train_scaled = scaler_x.transform(x_train)
    y_train_scaled = scaler_y.transform(y_train)
    x_test_scaled = scaler_x.transform(x_test)

    kernel = ConstantKernel() * RBF() + WhiteKernel()
    model = GaussianProcessRegressor(kernel=kernel)
    model.fit(x_train_scaled, y_train_scaled.flatten())

    y_mean, y_std = model.predict(x_test_scaled, return_std=True)

    y_target = min(y_train_scaled) - 0.01

    PoI = norm.cdf(y_target, y_mean, y_std)
    x_test["PoI"] = PoI
    print(x_test.sort_values(by="PoI", ascending=False).head(5))
