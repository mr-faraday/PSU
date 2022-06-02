<script setup>
import EmployeesApi from '@/api/employees-api'
import { computed, onMounted, ref } from 'vue'
import { useStore } from 'vuex'
import SpinnerIndicator from '@/components/SpinnerIndicator.vue'
import CreateEmployeeForm from '@/components/forms/CreateEmployeeForm.vue'
import { useToast } from 'vue-toastification'

const toast = useToast()
const store = useStore()

const user = computed(() => store.getters['user/info'])
const loading = ref(false)
const employees = ref([])
const form = ref(null)

const createEmployee = async (employeeData) => {
  try {
    loading.value = true

    const res = await EmployeesApi.create(employeeData)

    const credential = {
      login: res.data.result.login,
      password: res.data.result.password,
    }

    toast.success(`Сотрудник создан. Логин: ${credential.login}, пароль: ${credential.password}`)

    fetchEmployees()
    form.value?.clearForm()
  } catch (error) {
    toast.error(error.response?.data?.message ?? error.message)
    loading.value = false
  }
}

const deactivateEmployee = async ({ id }) => {
  try {
    loading.value = true

    await EmployeesApi.deactivate(id)

    fetchEmployees()
  } catch (error) {
    toast.error(error.response?.data?.message ?? error.message)
    loading.value = false
  }
}

const activateEmployee = async ({ id }) => {
  try {
    loading.value = true

    await EmployeesApi.activate(id)

    fetchEmployees()
  } catch (error) {
    toast.error(error.response?.data?.message ?? error.message)
    loading.value = false
  }
}

const fetchEmployees = async () => {
  try {
    loading.value = true

    const res = await EmployeesApi.get()

    employees.value = res.data.result
      .map((employee) => ({
        ...employee,
        roleName: store.getters.settings.userRoles.find((role) => role.id === employee.roleId).name,
      }))
      .sort((a, b) => a.id - b.id)
      .sort((a, b) => (a.active === b.active ? 0 : a.active ? -1 : 1))
  } catch (error) {
    toast.error(error.message)
  } finally {
    loading.value = false
  }
}

onMounted(fetchEmployees)
</script>

<template>
  <div v-if="loading" class="spinner-container">
    <SpinnerIndicator />
  </div>

  <template v-else>
    <div class="create-employee-form-container container">
      <CreateEmployeeForm ref="form" @submit="createEmployee" />
    </div>

    <div class="table-container">
      <table>
        <thead>
          <tr>
            <th>ID</th>
            <th>Логин</th>
            <th>Роль</th>
            <th>Имя</th>
            <th>Фамилия</th>
            <th>Действия</th>
          </tr>
        </thead>
        <tbody>
          <tr v-for="employee in employees" :key="employee.id">
            <td>{{ employee.id }}</td>
            <td>{{ employee.login }}</td>
            <td>{{ employee.roleName }}</td>
            <td>{{ employee.firstName }}</td>
            <td>{{ employee.lastName }}</td>
            <td v-if="employee.active">
              <button @click="deactivateEmployee(employee)" :disabled="employee.id === user.id">
                Деактивировать
              </button>
            </td>
            <td v-else>
              <button @click="activateEmployee(employee)" :disabled="employee.id === user.id">
                Активировать
              </button>
            </td>
          </tr>
        </tbody>
      </table>
    </div>
  </template>
</template>

<style lang="scss" scoped>
.create-employee-form-container {
  margin-bottom: 50px;
}
</style>
