<script setup>
import { onMounted, ref } from 'vue'
import SpinnerIndicator from '@/components/SpinnerIndicator.vue'
import TasksApi from '@/api/tasks-api';

const loading = ref(false)
const tasks = ref([])

const fetchTasks = async () => {
  try {
    loading.value = true

    const res = await TasksApi.get()

    tasks.value = res.data.result.sort((a, b) => a.id - b.id)
  } catch (error) {
    console.warn(error)
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
            <th>ID клиента</th>
            <th>Вес</th>
            <th>Время поступления</th>
          </tr>
        </thead>
        <tbody>
          <tr v-for="task in tasks" :key="task.id">
            <td>{{ cargo.id }}</td>
            <td>{{ cargo.clientId }}</td>
            <td>{{ cargo.weight }}</td>
            <td>{{ new Date(cargo.arrived_at) }}</td>
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
