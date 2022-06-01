<script setup>
import { defineEmits, ref, defineExpose } from 'vue'

const emit = defineEmits(['submit'])

const cargoId = ref('')

const submitHandler = async (e) => {
  e.preventDefault()

  if (!cargoId.value) {
    return alert('Не указан идентификатор ТМЦ')
  }

  emit('submit', cargoId.value)
}

defineExpose({
  clearForm() {
    cargoId.value = ''
  },
})
</script>

<template>
  <form class="create-employee-form" @submit="submitHandler">
    <h4>Возврат ТМЦ</h4>

    <div class="form-group">
      <input v-model="cargoId" placeholder="ID груза" />
    </div>

    <button type="submit">Отправить</button>
  </form>
</template>

<style lang="scss" scoped>
select {
  margin-bottom: 10px;
}
</style>
