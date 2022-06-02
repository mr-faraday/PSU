<script setup>
import { onMounted, ref } from 'vue'
import SpinnerIndicator from '@/components/SpinnerIndicator.vue'
import CreateClientForm from '@/components/forms/CreateClientForm.vue'
import ClientsApi from '@/api/clients-api'

const loading = ref(false)
const employees = ref([])
const form = ref(null)

const createClient = async (clientData) => {
  try {
    loading.value = true

    await ClientsApi.create(clientData)
    alert(`Клиент зарегестрирован.`)

    fetchClients()
    form.value.clearForm()
  } catch (error) {
    if (error.response?.data?.message) {
      alert(error.response.data.message)
    } else {
      console.warn(error)
    }

    loading.value = false
  }
}

const fetchClients = async () => {
  try {
    loading.value = true

    const res = await ClientsApi.get()

    employees.value = res.data.result.sort((a, b) => a.id - b.id)
  } catch (error) {
    if (error.response?.data?.message) {
      alert(error.response.data.message)
    } else {
      console.warn(error)
    }
  } finally {
    loading.value = false
  }
}

onMounted(fetchClients)
</script>

<template>
  <div v-if="loading" class="spinner-container">
    <SpinnerIndicator />
  </div>

  <template v-else>
    <div class="create-client-form-container container">
      <CreateClientForm ref="form" @submit="createClient" />
    </div>

    <div class="table-container">
      <table>
        <thead>
          <tr>
            <th>ID</th>
            <th>Имя</th>
            <th>Фамилия</th>
            <th>Телефон</th>
          </tr>
        </thead>
        <tbody>
          <tr v-for="employee in employees" :key="employee.id">
            <td>{{ employee.id }}</td>
            <td>{{ employee.firstName }}</td>
            <td>{{ employee.lastName }}</td>
            <td>{{ employee.phone }}</td>
          </tr>
        </tbody>
      </table>
    </div>
  </template>
</template>

<style lang="scss" scoped>
.create-client-form-container {
  margin-bottom: 50px;
}

.table-container {
  table {
    width: 100%;
  }
  th {
    text-align: left;
  }
}
</style>
