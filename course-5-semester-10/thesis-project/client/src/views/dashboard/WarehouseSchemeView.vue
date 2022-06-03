<script setup>
import { onMounted, onUnmounted, ref } from 'vue'
import SpinnerIndicator from '@/components/SpinnerIndicator.vue'
import { useToast } from 'vue-toastification'
import WarehouseApi from '@/api/warehouse-api'
import Chart from 'chart.js/auto'

const toast = useToast()

const loading = ref(false)
const chart = ref(null)

/* eslint-disable */

const CHART_COLORS = {
  red: 'rgb(255, 99, 132)',
  orange: 'rgb(255, 159, 64)',
  yellow: 'rgb(255, 205, 86)',
  green: 'rgb(75, 192, 192)',
  blue: 'rgb(54, 162, 235)',
  purple: 'rgb(153, 102, 255)',
  grey: 'rgb(201, 203, 207)',
}

const getCahrtConfig = (data) => ({
  type: 'bar',
  data,
  options: {
    plugins: {
      title: {
        display: true,
        text: 'Статистика по занятому месту',
      },
    },
    responsive: true,
    scales: {
      x: {
        stacked: true,
      },
      y: {
        stacked: true,
      },
    },
  },
})

const initChart = async () => {
  try {
    loading.value = true
    const res = await WarehouseApi.getShelfOcupations()
    const rawData = res.data.result
      .map((shelf) => ({
        ...shelf,
        ocupiedPositionCount: Number(shelf.ocupiedPositionCount),
        reservedPositionCount: Number(shelf.reservedPositionCount),
        willFreeShorltyPositionCount: Number(shelf.willFreeShorltyPositionCount),
      }))
      .sort((a, b) => a.rackId - b.rackId)
      .sort((a, b) => a.id - b.id)

    const data = rawData.map((s) => ({
      label: `полка ${s.id} (c.${s.rackId})`,
      ocupied: s.ocupiedPositionCount - s.willFreeShorltyPositionCount,
      reserved: s.reservedPositionCount,
      willFree: s.willFreeShorltyPositionCount,
      free: s.positionQuantity - s.ocupiedPositionCount - s.reservedPositionCount,
    }))

    const labels = data.map((s) => s.label)
    const datasets = [
      {
        label: 'Занято',
        data: data.map((s) => s.ocupied),
        backgroundColor: CHART_COLORS.blue,
      },
      {
        label: 'Скоро освободятся',
        data: data.map((s) => s.willFree),
        backgroundColor: CHART_COLORS.green,
      },
      {
        label: 'Зарезервировано',
        data: data.map((s) => s.reserved),
        backgroundColor: CHART_COLORS.yellow,
      },
      {
        label: 'Свободно',
        data: data.map((s) => s.free),
        backgroundColor: CHART_COLORS.grey,
      },
    ]

    loading.value = false
    await new Promise((r) => requestAnimationFrame(r))
    await new Promise((r) => requestAnimationFrame(r))

    const canvas = document.getElementById('chart')
    chart.value = new Chart(canvas, getCahrtConfig({ labels, datasets }))
  } catch (error) {
    toast.error(error.message)
  } finally {
    loading.value = false
  }
}

onMounted(initChart)
onUnmounted(() => {
  if (chart.value) {
    chart.value.destroy()
  }
})
</script>

<template>
  <div v-if="loading" class="spinner-container">
    <SpinnerIndicator />
  </div>

  <div v-else class="chart-container">
    <canvas id="chart"></canvas>
  </div>
</template>

<style lang="scss" scoped>
.chart-container {
  position: relative;
  height: 80vh;
}
</style>
