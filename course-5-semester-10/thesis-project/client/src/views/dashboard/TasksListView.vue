<script setup>
import { computed, onMounted, ref } from 'vue'
import SpinnerIndicator from '@/components/SpinnerIndicator.vue'
import TasksApi from '@/api/tasks-api'
import { useStore } from 'vuex'
import { TaskStatusId, UserRoleId } from '@/constants'
import { useToast } from 'vue-toastification'

const store = useStore()
const toast = useToast()

const loading = ref(false)
const tasks = ref([])
const taskStatuses = computed(() => store.getters.settings.taskStatuses)

const completeTask = async (id) => {
  try {
    loading.value = true

    await TasksApi.complete(id)

    toast.success(`Задача выполнена`)

    fetchTasks()
  } catch (error) {
    toast.error(error.response?.data?.message ?? error.message)
    loading.value = false
  }
}

const authorizedCompleteTas = computed(() => {
  const user = store.getters['user/info']

  return [UserRoleId.ADMIN, UserRoleId.MANAGER].includes(user.roleId)
})

const fetchTasks = async () => {
  try {
    loading.value = true

    const res = await TasksApi.get()

    tasks.value = res.data.result
      .sort((a, b) => a.id - b.id)
      // sort by status
      .sort((a, b) => {
        if (a.statusId === TaskStatusId.DONE) return 1
        if (b.statusId === TaskStatusId.DONE) return -1
        return 0
      })
      .map((task) => ({
        ...task,
        statusName: taskStatuses.value.find((status) => status.id === task.statusId).name,
      }))
  } catch (error) {
    toast.error(error.message)
  } finally {
    loading.value = false
  }
}

onMounted(fetchTasks)
</script>

<template>
  <div v-if="loading" class="spinner-container">
    <SpinnerIndicator />
  </div>

  <template v-else>
    <div class="table-container">
      <table>
        <thead>
          <tr>
            <th>ID</th>
            <th>ID груза</th>
            <th>Статус</th>
            <th>Тип</th>
            <th>Дата создания</th>
            <th>Дeйствия</th>
          </tr>
        </thead>
        <tbody>
          <tr v-for="task in tasks" :key="task.id">
            <td>{{ task.id }}</td>
            <td>{{ task.cargoId }}</td>
            <td>{{ task.statusName }}</td>
            <td>{{ task.sourcePosition ? 'Возврат' : 'Поступление' }}</td>
            <td>{{ new Date(task.createdAt).toLocaleString() }}</td>
            <td>
              <button
                v-if="authorizedCompleteTas && TaskStatusId.NEW === task.statusId"
                type="button"
                @click="completeTask(task.id)"
              >
                Завершить
              </button>
            </td>
          </tr>
        </tbody>
      </table>
    </div>
  </template>
</template>

<style lang="scss" scoped>
.table-container {
  table {
    width: 100%;
  }
  th {
    text-align: left;
  }
}
</style>
