<script setup>
import dashboardItems from '@/router/dashboard'
import { computed } from '@vue/runtime-core'
import { useStore } from 'vuex'

const store = useStore()

const user = computed(() => store.getters['user/info'])
const items = computed(() => dashboardItems.filter((item) => item.roles.includes(user.value.roleId)))
</script>

<template>
  <nav class="control-pannel">
    <ul>
      <li v-for="(item, i) in items" :key="i">
        <router-link :to="item.href" class="nav-item">{{ item.name }}</router-link>
      </li>
    </ul>
  </nav>
</template>



<style lang="scss">
.scroll {
  height: calc(100vh - 64px);
  overflow-y: auto;

  &::-webkit-scrollbar {
    width: 10px;
  }
  &::-webkit-scrollbar-track {
    background: #f1f1f1;
  }
  &::-webkit-scrollbar-thumb {
    background: var(--primary-color);
  }
  &::-webkit-scrollbar-thumb:hover {
    background: #555;
  }
}

nav.control-pannel {
  @extend .scroll;
  width: 320px;
  background-color: var(--black);

  ul {
    list-style-type: none;
    padding: 0 var(--horizontal-padding);
  }

  .nav-item {
    color: white;
    text-decoration: none;
    display: block;
    padding: 12px 0;
    display: flex;
    align-items: center;
    transition: all 0.15s;

    &:hover {
      color: grey;
    }
  }
  .nav-item.active {
    color: var(--primary-color);
  }
}

.operation-window {
  @extend .scroll;

  flex: 1;
  padding-bottom: 20px;

  input:not([type='submit']) {
    margin-bottom: 10px;
    width: 400px;
  }

  p {
    white-space: pre-line;
  }
}
</style>
