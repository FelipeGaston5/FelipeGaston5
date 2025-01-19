import pandas as pd
import numpy as np

from sklearn.model_selection import train_test_split
from sklearn.linear_model import LinearRegression
from sklearn.metrics import mean_absolute_error, mean_squared_error

db = pd.read_csv('machine_learning/python/casas_preco_eda.csv')

db = db.drop(columns=['titulo', 'descriçao', 'casas'])
    
print(db.info())

x = db[['quartos', 'banheiro']]
y = db['preco']

x_treino, x_teste, y_treino, y_teste = train_test_split(x, y, test_size=0.2, random_state=42)

modelos = LinearRegression()
modelos.fit(x_treino, y_treino)

y_pred = modelos.predict(x_teste)

mae = mean_absolute_error(y_teste, y_pred)
rmse = np.sqrt(mean_squared_error(y_teste, y_pred))

print()
print()

print("<<<======RESULTADOS=======>>>")
print()
print(f'mae: {mae:.2f}')
print()
print(f'rmse: {rmse:.2f}')
print("<<<========================>>>")