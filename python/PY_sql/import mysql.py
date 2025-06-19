import mysql.connector
from faker import Faker
import random

# 🔗 Conexão com o MySQL
conn = mysql.connector.connect(
    host='localhost',
    user='root',
    password='root',
    database='quarteto_motors'
)

cursor = conn.cursor()
fake = Faker('pt_BR')

# 🔄 Função para inserir dados
def inserir_dados(query, valores):
    try:
        cursor.executemany(query, valores)
        conn.commit()
        print(f"{cursor.rowcount} registros inseridos com sucesso!")
    except Exception as e:
        print(f"Erro ao inserir: {e}")

# 🚗 **Inserindo Concessionárias**
concessionarias = [
    (
        fake.company(), 
        fake.address().replace("'", ""), 
        fake.cnpj().replace('.', '').replace('/', '').replace('-', ''), 
        fake.phone_number().replace("(", "").replace(")", "").replace(" ", "").replace("-", "")[:11]
    )
    for _ in range(10)
]

query_concessionaria = """
    INSERT INTO concessionaria (nome, endereco, CNPJ, telefone) 
    VALUES (%s, %s, %s, %s)
"""
inserir_dados(query_concessionaria, concessionarias)

# 🔍 **Verificando IDs de Concessionárias**
cursor.execute("SELECT id_concessionaria FROM concessionaria")
ids_concessionarias = [id[0] for id in cursor.fetchall()]
print("Concessionárias encontradas:", ids_concessionarias)

# 👥 **Inserindo Clientes**
clientes = [
    (
        fake.name(), 
        fake.cpf().replace('.', '').replace('-', ''), 
        fake.address().replace("'", ""), 
        fake.phone_number().replace("(", "").replace(")", "").replace(" ", "").replace("-", "")[:11], 
        fake.email()
    )
    for _ in range(500)
]

query_cliente = """
    INSERT INTO cliente (nome, CPF, endereco, telefone, email) 
    VALUES (%s, %s, %s, %s, %s)
"""
inserir_dados(query_cliente, clientes)

# 👨‍🔧 **Inserindo Funcionários**
funcionarios = [
    (
        fake.name(),
        fake.cpf().replace('.', '').replace('-', ''),
        fake.address().replace("'", ""),
        fake.phone_number().replace("(", "").replace(")", "").replace(" ", "").replace("-", "")[:11],
        fake.email(),
        random.choice(['Vendedor', 'Mecânico', 'Gerente']),
        random.choice(ids_concessionarias)
    )
    for _ in range(500)
]

query_funcionario = """
    INSERT INTO funcionarios (nome, CPF, endereco, telefone, email, cargo, concessionaria_id) 
    VALUES (%s, %s, %s, %s, %s, %s, %s)
"""
inserir_dados(query_funcionario, funcionarios)

# 🚗 **Inserindo Carros**
modelos = ["Gol", "Up!", "Onix", "HB20", "Civic", "Corolla", "Sandero", "Kwid", "Polo", "Uno"]
carros = [
    (
        random.choice(modelos),
        random.randint(2015, 2025),
        fake.license_plate().replace("-", ""),
        fake.color_name()[:10],  # Limita o nome da cor a 10 caracteres
        random.randint(20000, 100000),
        random.choice(ids_concessionarias)
    )
    for _ in range(500)
]

query_carros = """
    INSERT INTO carros (modelo, ano, placa, cor, preco, concessionaria_id) 
    VALUES (%s, %s, %s, %s, %s, %s)
"""
inserir_dados(query_carros, carros)

# 🔌 **Fechando a conexão**
cursor.close()
conn.close()